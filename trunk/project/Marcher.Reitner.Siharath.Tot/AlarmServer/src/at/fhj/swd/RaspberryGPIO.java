package at.fhj.swd;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class RaspberryGPIO implements GPIO {
	
	private int gpio;
	private boolean setupSuccess;
	private String gpioMainPath = "/sys/class/gpio";
	private String gpioPinPath = gpioMainPath+ "/gpio%s";
	private String gpioPinValuePath;
	private String direction;
	
	public RaspberryGPIO(int gpio, String direction) {
		this.gpio = gpio;
		this.direction = direction;
		gpioPinPath = String.format(gpioPinPath, Integer.toString(gpio));
		gpioPinValuePath = gpioPinPath + "/value";
		setupSuccess = setupGPIO();
	}

	
	private boolean directoryExists(String directory)
	{
		File stats = new File(directory);
		if (stats.exists())    // Überprüfen, ob es den Ordner gibt
		{
			return true;
		}
		else return false;
	}

	private boolean setupGPIO() {
		// GPIO needs to be exported
		// After that, the direction (in/out) needs to be set
		String strGpio = Integer.toString(gpio);
		
		if (!directoryExists(gpioPinPath)) {
	
			// Export
			if (writeGpioData(gpioMainPath+ "/export", strGpio))
				// Direction
				if (writeGpioData(gpioPinPath+ "/direction", direction))
					return true;
		} else return true;
		
		return false;
	}
	
	private boolean writeGpioData(String file, String value) {
		BufferedWriter out = null;
		try  
		{
			Logger.log("Trying to write to file '" + file + "'");
		    FileWriter fstream = new FileWriter(file, false); //true tells to append data.
		    out = new BufferedWriter(fstream);
		    out.write(value);
		}
		catch (IOException e)
		{
		    Logger.log("Error: " + e.getMessage());
		}
		finally
		{
		    if(out != null) {
		        try {
					out.close();
					Logger.log("Successfully written!");
					return true;
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
		    }
		}
		return false;
	}

	@Override
	public void on() {
		if (setupSuccess) {
			writeGpioData(gpioPinValuePath, "1");
		} else {
			Logger.log("Setup was not successfull!");
		}
	}
	
	@Override
	public void off() {
		if (setupSuccess) {
			writeGpioData(gpioPinValuePath, "0");
		} else {
			Logger.log("Setup was not successfull!");
		}
	}

}
