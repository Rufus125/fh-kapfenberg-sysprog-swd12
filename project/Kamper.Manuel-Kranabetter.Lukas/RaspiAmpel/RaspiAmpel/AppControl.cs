using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace RaspiAmpel
{
    /// <summary>
    /// Controller für die Befehle der App und die Ausgabe in die Konsole
    /// by Manuel Kamper
    /// </summary>
    class AppControl
    {
        internal static int lastMessage = 0;

        /// <summary>
        /// Reagiert auf Steuerbefehle
        /// S-Taste: schaltet Ampel ein und aus
        /// I-Taste: gibt Statusinfos zur Ampel zurück
        /// H-Taste: Umschalten zwischen Automatikmodus oder Handbetrieb
        /// X-Taste: sicheres Programmende
        /// </summary>
        internal static void CheckForKey()
        {
            ConsoleKeyInfo cki = new ConsoleKeyInfo();
            while (true)
            {
                while (Console.KeyAvailable == false)
                    Thread.Sleep(250);
                cki = Console.ReadKey(true);
                if (cki.Key == ConsoleKey.S) //ein/aus schalten
                {
                    lastMessage = Ampel.heartbeatCount;
                    if (!Ampel.onoffRequest)
                    {
                        Ampel.onoffRequest = true;
                        OverwriteLine(1, 6, "switched traffic lights " + (Ampel.ampelAktiv ? "off" : "on")); //todo: korrigieren
                    }
                    else
                    {
                        OverwriteLine(1, 6, "not allowed; traffic light is switching " + (Ampel.ampelAktiv ? "off" : "on"));
                    }
                }
                else if (cki.Key == ConsoleKey.I) //info anzeigen
                {
                    lastMessage = Ampel.heartbeatCount;
                    OverwriteLine(1, 6, "traffic lights are " + (Ampel.ampelAktiv ? "on" : "off") + (Ampel.onoffRequest ? " (currently switching " + (Ampel.ampelAktiv ? "off" : "on") + ")" : "") + "; current mode: " + (Ampel.ampelAuto ? "auto" : "manual"));
                }
                else if (cki.Key == ConsoleKey.H) //modus auto/hand umschalten
                {
                    //todo: ampel von automatisch auf händisch umschalten; phasen-timer aushebeln - grün blinkend berücksichtigen!
                    Ampel.ampelAuto = !Ampel.ampelAuto;
                    lastMessage = Ampel.heartbeatCount;
                    OverwriteLine(1, 6, "switched traffic light mode to " + (Ampel.ampelAuto ? "auto" : "manual"));
                }
                else if (cki.Key == ConsoleKey.X) //ampel beenden
                {
                    GpioControl.AlleAus();
                    Environment.Exit(0);
                }
                else if(cki.Key==ConsoleKey.P) //nächste phase (nur bei handmodus)
                {
                    GpioControl.RequestPhase();
                }
                else if(cki.Key==ConsoleKey.F) //fußgänger re-li
                {
                    GpioControl.RequestWalker(1);
                }
                else if(cki.Key==ConsoleKey.G) //fußgänger ob-un
                {
                    GpioControl.RequestWalker(2);
                }
            }
        }

        /// <summary>
        /// Löscht den Zeileninhalt ab einer bestimmten Startposition bis zum Ende und setzt den Cursor wieder auf die Startposition.
        /// </summary>
        /// <param name="left">Abstand von links, beginnend bei 0</param>
        /// <param name="top">Abstand von oben, beginnend bei 0</param>
        internal static void ResetLine(int left, int top)
        {
            Console.SetCursorPosition(left, top);
            Console.Write(new String(' ', Console.BufferWidth));
            Console.SetCursorPosition(left, top);
        }

        /// <summary>
        /// Überschreibt eine komplette Zeile, ohne dass Rückstände der alten zurück bleiben.
        /// </summary>
        /// <param name="left">Abstand von links, beginnend bei 0</param>
        /// <param name="top">Abstand von oben, beginnend bei 0</param>
        /// <param name="consoleText">Text der in Konsole ausgegeben werden soll</param>
        internal static void OverwriteLine(int left, int top, string consoleText)
        {
            ResetLine(left, top);
            Console.WriteLine(consoleText);
        }
    }
}
