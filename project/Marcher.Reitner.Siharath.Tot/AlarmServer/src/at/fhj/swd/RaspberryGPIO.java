package at.fhj.swd;

import java.io.File;
import java.io.IOException;

public class RaspberryGPIO implements GPIO {
	
	private int gpio;
	
	public RaspberryGPIO(int gpio) {
		this.gpio = gpio;
		setupGPIO("out");
	}

	private void executeLinuxCommand(String command) {
		try {
			Process p = Runtime.getRuntime().exec(command);
			p.waitFor();
			
		} catch (IOException | InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	private void setupGPIO(String string) {
		String strGpio = Integer.toString(gpio);
		Logger.log("Setting up GPIO "+ strGpio);
		String path = "/sys/classes/gpio";
		File f = new File(path);
		if (f.exists() && f.isDirectory()) {
			String command = "echo \""+ strGpio +"\" > "+ path+ "/export";
			Logger.log(command);
			executeLinuxCommand(command);
		} else {
			Logger.log("Path not found: "+ path);
		}
	}

	@Override
	public void on() {
		String path = "/sys/classes/gpio/gpio"+ Integer.toString(gpio);
		File f = new File(path);
		if (f.exists() && f.isDirectory()) {
			String command = "echo \"1\" > "+ path+ "/value";
			Logger.log(command);
			executeLinuxCommand(command);
		} else {
			Logger.log("Path not found: "+ path);
		}
	}
	
	@Override
	public void off() {
		String path = "/sys/classes/gpio/gpio"+ Integer.toString(gpio);
		File f = new File(path);
		if (f.exists() && f.isDirectory()) {
			String command = "echo \"0\" >"+ path+ "/value";
			Logger.log(command);
			executeLinuxCommand(command);
		} else {
			Logger.log("Path not found: "+ path);
		}
	}

}
