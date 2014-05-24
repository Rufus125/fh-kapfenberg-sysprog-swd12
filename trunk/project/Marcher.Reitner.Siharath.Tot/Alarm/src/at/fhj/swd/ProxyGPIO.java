package at.fhj.swd;

import java.io.IOException;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.net.Socket;

public class ProxyGPIO implements GPIO {

	//Baut Socketverbindung auf und schickt "on" oder "off"
	
	private String host;
	private int port;

	public ProxyGPIO(String host, int port) {
		this.host = host;
		this.port = port;
	}
	
	private void sendToSocket(String command) {
		Socket socket = null;
		try {
			socket = new Socket(host, port);
			OutputStream outstream = null;
			outstream = socket.getOutputStream();
			PrintWriter out = new PrintWriter(outstream);;
			out.print(command+"\n");
			out.flush();
			socket.close();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
    }

	@Override
	public void on() {
		// TODO Auto-generated method stub
		System.out.println(" ClientGPIO sends: ON");
		sendToSocket("on");
		System.out.println(" Done!");
	}

	@Override
	public void off() {
		// TODO Auto-generated method stub
		System.out.println(" ClientGPIO sends: OFF");
		sendToSocket("off");
		System.out.println(" Done!");
	}

}
