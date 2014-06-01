using System;
using System.Threading;
using System.Collections.Generic;

using LibPiGpio;

namespace RPiBlinky
{
	/// <summary>
	/// Testprogramm für alle output pins
	/// by Manuel Kamper, Lukas Kranabetter
	/// </summary>
	class Program
	{
		// Gpio numbers for all modes - read "Ampel-GPIO Zuweisung.xlsx" for further informations
		internal static int[] gpioOut = new int[] { 17, 18, 22, 23, 24, 25, 4, 7, 8, 9 };
		internal static int[] gpioRed = new int[] { 17, 23, 4, 8 };
		internal static int[] gpioYellow = new int[] { 18, 24 };
		internal static int[] gpioGreen = new int[] { 22, 25, 7, 9 };
        
        // Currently gpio on to watch maximum power need
        internal static uint gpioMaxOn = 8;
        internal static List<int> gpioOn = new List<int>();
        
		// Current testing mode
		internal static string mode = "default";
		internal static string previousMode = "default";
       
		// Testing mode flashing flag
		internal static bool flashing = false;
        
        // Console key event listener as separated thread
		internal static Thread ConsoleKeyListener;
        
		/// <summary>
		/// Main method for test program
		/// </summary>
		static void Main(string[] args)
		{
			// Programmbeschreibung
			Console.Clear();
			Console.WriteLine("RaspiAmpel v0.1 - Build 17.05.2014");
			Console.WriteLine("by Manuel Kamper & Lukas Kranabetter");
			Console.WriteLine("====================================");
			Console.WriteLine("Keys for testing modes:");
			Console.WriteLine("r (all red ones)");
			Console.WriteLine("y (all yellow ones)");
			Console.WriteLine("g (all green ones)");
			Console.WriteLine("a (all, maximum 8 leds at once - power limit)");
			Console.WriteLine("o (all off)");
			Console.WriteLine("d (disco)");
			Console.WriteLine("f (flashing mode, available for all modes except disco and off mode)");
			Console.WriteLine("x (exit)");
           
			// Initailize needed pins 
			RpiGpio.SetOutputPins(gpioOut);
			
			// Start key listener
			ConsoleKeyListener = new Thread(new ThreadStart(ConsoleKeyEvent));
			ConsoleKeyListener.Name = "ConsoleKeyListener";
            ConsoleKeyListener.Start();
            
            // Test loop, program exit with key x
			while(true) 
			{
				GpioTest();
				Console.WriteLine("--------------------");
                
				// Wait for next check
				Thread.Sleep(1000);
			}
		}
        
		/// <summary>
		/// Listen to key inputs for switching test modes
		/// </summary>
		internal static void ConsoleKeyEvent()
		{
			while(true)
			{
				// Get key value and switch testing mode
				switch(Console.ReadKey(true).Key) 
				{
					case ConsoleKey.R:
						mode = "red";
					break;
			           
					case ConsoleKey.Y:
						mode = "yellow";
					break;
			           
					case ConsoleKey.G:
						mode = "green";
					break;
			           
					case ConsoleKey.A:
						mode = "all";
					break;
			           
					case ConsoleKey.O:
						mode = "off";
					break;
			           
					case ConsoleKey.D:
						mode = "disco";
					break;
			           
					case ConsoleKey.F:
						flashing = !flashing;
					break;
			           
					case ConsoleKey.X:
						mode = "exit";	               
					break;
					
					default:
					    mode = previousMode;
					break;
				}
				
				Console.WriteLine("Switch testing mode to: " + mode);
			}
		}
        
		/// <summary>
		/// Run gpio test by mode setting
		/// </summary>
		internal static void GpioTest()
		{
			// TODO: After switching back from flashing can be all leds are off
			if(mode != previousMode) 
			{
				// Reset gpios when mode has been switched
				GpioAllOff();
				previousMode = mode;
			} 
			else if(!flashing && mode != "disco") 
			{
				// Only flashing and disco need led updates after a loop
				return;
			}
           
			// TODO: Seems at least the #define NOPI test mode always return 0 for a gpio value
			switch(mode) 
			{
			    case "red":
               
					foreach(int gpio in gpioRed) 
					{
						RpiGpio.Pins[gpio] = (flashing) ? !RpiGpio.Pins[gpio] : true;
						gpioOn.Add(gpio);
					}
			         	               
				break;
	           
			    case "yellow":
			   
					foreach(int gpio in gpioYellow) 
					{
						RpiGpio.Pins[gpio] = (flashing) ? !RpiGpio.Pins[gpio] : true;
						gpioOn.Add(gpio);
					}
			        
				break;
	           
			    case "green":
	           
					foreach(int gpio in gpioGreen) 
					{
						RpiGpio.Pins[gpio] = (flashing) ? !RpiGpio.Pins[gpio] : true;
						gpioOn.Add(gpio);
					}
			         
				break;
	           
			    case "all":
	           
					foreach(int gpio in gpioOut) 
					{
						RpiGpio.Pins[gpio] = (flashing) ? !RpiGpio.Pins[gpio] : true;
						gpioOn.Add(gpio);
				            
						if(gpioOn.Count >= gpioMaxOn) break;
					}
			         
				break;
	           
			    case "off":
	           
				    GpioAllOff();
			        
				break;
	           
			    case "disco":
	              
					Random random = new Random();
					
					// TODO: Should work without set all off before, improve!!
					GpioAllOff();
					
					foreach(int gpio in gpioOut) 
					{
						bool on = random.NextDouble() > 0.5;
						
						RpiGpio.Pins[gpio] = on;
						
						if(on)
						{
					        gpioOn.Add(gpio);   
						}
						else
						{
						    gpioOn.Remove(gpio);
						}
						
						if(gpioOn.Count >= gpioMaxOn) break;
					}
			        
				break;
	           
			    case "exit":
			        
			        // Set all leds off, abort key listener and exit program 
					GpioAllOff();					
					ConsoleKeyListener.Abort(); 
					Environment.Exit(0);
	               
				break;
			}
		}
        
		/// <summary>
		/// Set all leds off
		/// </summary>
		internal static void GpioAllOff()
		{
			foreach(int gpio in gpioOut) 
			{
				RpiGpio.Pins[gpio] = false;
			}
			
			gpioOn = new List<int>();
		}       
	}
}