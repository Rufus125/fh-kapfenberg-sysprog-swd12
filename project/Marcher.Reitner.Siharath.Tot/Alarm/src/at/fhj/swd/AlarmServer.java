package at.fhj.swd;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.ServerSocket;
import java.net.Socket;

public class AlarmServer {

	public static void main(String[] args) {
		System.out.println("Server started");
		if (args.length == 1) {
			int port = Integer.parseInt(args[0]);
			
			RaspberryGPIO server = new RaspberryGPIO();
			
			int portNumber = Integer.parseInt(args[0]);
	         
	        try (
	            ServerSocket serverSocket = new ServerSocket(port);
	            Socket clientSocket = serverSocket.accept();                
	            BufferedReader in = new BufferedReader(
	                new InputStreamReader(clientSocket.getInputStream()));
	        	) {
	        		//run and run and run....
	        		while(true) {
		            	String action;
		            	while ((action = in.readLine()) != null) {
		            		// hier könnte man noch einen Thread starten, der die Events behandelt
		            		System.out.println(action);
		            		switch (action) {
		        			case "on":
		        				server.on();
		        				break;
		        			case "off":
		        				server.off();
		        			}
		            	}
	        		}
	        	} catch (IOException e) {
	        		System.out.println("Exception caught when trying to listen on port "
	        				+ portNumber + " or listening for a connection");
	        		System.out.println(e.getMessage());
	        	}
			
		} else {
			System.out.println("  Invalid arguments!\n  Syntax: AlarmServer [{PORT}]\n  Example: AlarmServer 2999");
		}
		System.out.println("Server ended");
	}

}
