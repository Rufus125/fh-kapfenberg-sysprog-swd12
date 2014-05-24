package at.fhj.swd;

public class AlarmClient {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		//Parameter:
		//IP: 192.168.2.34
		//Port: 2999
		//State: on/off
		
		System.out.println("Start");
		
		String host ="localhost";
		int port = 2999;
		
		if (args.length == 3) {
			System.out.println(args[0]);
			host = args[0];
			System.out.println(args[1]);
			port = Integer.parseInt(args[1]);
			System.out.println(args[2]);
			
			ClientGPIO client = new ClientGPIO(host, port);
			
			switch (args[2].toLowerCase()) {
			case "on":
				client.on();
				break;
			case "off":
				client.off();
			}
		} else {
			System.out.println("Invalid arguments!\nSyntax: AlarmClient [{HOST}] [{PORT}] [{STATE}]\nExample: AlarmClient 192.168.1.12 2999 on");
		}
		
		System.out.println("End");
	}

}
