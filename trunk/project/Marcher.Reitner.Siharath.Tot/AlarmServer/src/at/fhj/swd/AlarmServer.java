package at.fhj.swd;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;

public class AlarmServer {

	public static void main(String[] args) {
		if (args.length == 1) {
			int port = Integer.parseInt(args[0]);
			Logger.log("Server started");
			
			Logger.log("Listening to port: "+ Integer.toString(port));
	         
			ServerSocket server = null;
			try
			{
				server = new ServerSocket(port);
				Logger.log("RPC Server is running...");
				while (true)
				{
					Socket connection = server.accept(); // wait for a connection
					Logger.log("connection: " + connection.toString());
					try
					{					
						BufferedReader in = new BufferedReader(new InputStreamReader(connection.getInputStream()));
						PrintWriter out = new PrintWriter(connection.getOutputStream());

						String[] action = in.readLine().split(",");
		            	Logger.log("received: "+ action[0]+","+action[1]);
		            	int gpio = Integer.parseInt(action[0]);
		            	
		            	RaspberryGPIO raspberryGPIO = new RaspberryGPIO(gpio, "out");
		            	
		            	switch (action[1]) {
		        			case "on":
		        				raspberryGPIO.on();
		        				break;
		        			case "off":
		        				raspberryGPIO.off();
		        				break;
		        		}
		            	
		            	String response = "Action done: GPIO: "+ action[0]+ ", ACTION: "+ action[1]+ "\n";
						out.print(response);
						out.flush();
						
						connection.close();
					} 
					catch(Exception e)
					{
						e.printStackTrace();
					} 
					finally
					{
						if (connection != null)
							connection.close();
					}
				}
			} 
			catch (IOException e)
			{
				e.printStackTrace();
			}
			finally
			{
				try
				{
					if(server != null)
					server.close();
				}
				catch (IOException e)
				{
					e.printStackTrace();
				}
			}			
		} else {
			Logger.log("  Invalid arguments!\n  Syntax: AlarmServer [{PORT}]\n  Example: AlarmServer 2999");
		}
		Logger.log("Server ended");
	}

}
