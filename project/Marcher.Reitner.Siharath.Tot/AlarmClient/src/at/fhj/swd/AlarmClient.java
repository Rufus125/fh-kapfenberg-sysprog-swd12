package at.fhj.swd;


public class AlarmClient {

	public static void startClient(String[] args) {
		//Parameter:
		//IP: 192.168.2.34
		//Port: 2999
		//GPIO: 23
		//State: on/off
		
		Logger.log("Client started");
		
		printArgs(args);
		
		if (args.length == 5) {
			String host = args[1];
			int port = Integer.parseInt(args[2]);
			int gpio = Integer.parseInt(args[3]);
			String action = args[4].toLowerCase();
			
//			action = "on";
//			action = "off";
			
			ProxyGPIO proxyGPIO = new ProxyGPIO(host, port, gpio);
			
			switch (action) {
			case "on":
				proxyGPIO.on();
				break;
			case "off":
				proxyGPIO.off();
				break;
			}
		} else {
			Logger.log("  Invalid arguments!\n  Syntax: AlarmClient [{HOST}] [{PORT}] [{GPIO}] [{STATE}]\n  Example: AlarmClient 192.168.1.12 2999 23 on");
		}
		
		Logger.log("Client ended");
	}

	private static void printArgs(String[] args) {
		Logger.log("  Given parameters:");
		for (int i = 0; i < args.length; i++) {
			Logger.log("    param "+ Integer.toString(i) + ": "+ args[i]);
		}
	}

}
