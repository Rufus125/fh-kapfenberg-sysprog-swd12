package at.fhj.swd;

public class AlarmClient {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		//Parameter:
		//IP: 192.168.2.34
		//Port: 2999
		//State: on/off
		
		System.out.println("Client started");
		
		printArgs(args);
		
		if (args.length == 3) {
			String host = args[0];
			int port = Integer.parseInt(args[1]);
			String action = args[2].toLowerCase();
			
			ProxyGPIO client = new ProxyGPIO(host, port);
			
			switch (action) {
			case "on":
				client.on();
				break;
			case "off":
				client.off();
			}
		} else {
			System.out.println("  Invalid arguments!\n  Syntax: AlarmClient [{HOST}] [{PORT}] [{STATE}]\n  Example: AlarmClient 192.168.1.12 2999 on");
		}
		
		System.out.println("Client ended");
	}

	private static void printArgs(String[] args) {
		System.out.println("  Given parameters:");
		for (int i = 0; i < args.length; i++) {
			System.out.println("    param "+ Integer.toString(i) + ": "+ args[i]);
		}
	}

}
