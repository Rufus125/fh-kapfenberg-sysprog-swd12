package at.fhj.swd;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;
import java.net.UnknownHostException;

public class ProxyGPIO implements GPIO {

	//Baut Socketverbindung auf und schickt "on" oder "off"
	
	private String host;
	private int port;
	private int gpio;

	public ProxyGPIO(String host, int port, int gpio) {
		this.host = host;
		this.port = port;
		this.gpio = gpio;
	}
	
	private String sendToSocket(String command) {
		Socket socket = null;
		try
		{
			socket = new Socket(host, port);
			Logger.log("    connect to " + socket);
			
			// send request
			Logger.log("    send: '" + command + "'");
			PrintWriter out = new PrintWriter(socket.getOutputStream());		
			out.println(command+"\n");
			out.flush();

			// read response
			BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
			String response = in.readLine();
			
			Logger.log("    receive: '"+ response +"'");
			
			in.close();
			out.close();
			socket.close();

			return response;
		}
		catch(UnknownHostException e)
		{
			e.printStackTrace();
		}
		catch(IOException e)
		{
			e.printStackTrace();
		}
		return null;
    }

	@Override
	public void on() {
		String strGpio =  Integer.toString(gpio);
		Logger.log(" ClientGPIO sends: ON for GPIO "+strGpio);
		String command = new StringBuilder().append(strGpio).append(",").append("on").toString();
		String response = sendToSocket(command);
		if (response == null) {
			Logger.log(" Error! There was no response: "+ response);
		} else {
			Logger.log(" Sending Successfull!");
		}
	}

	@Override
	public void off() {
		String strGpio =  Integer.toString(gpio);
		Logger.log(" ClientGPIO sends OFF for GPIO "+strGpio);
		String command = new StringBuilder().append(strGpio).append(",").append("off").toString();
		String response = sendToSocket(command);
		if (response == null) {
			Logger.log(" Error! There was no response: "+ response);
		} else {
			Logger.log(" Sending Successfull!");
		}
	}

}
