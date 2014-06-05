package at.fhj.swd;

import java.util.Date;

public class Logger
{
	private Logger() {}
	
	
	public static void log(String msg)
	{		
		System.out.println("[" + timeStamp() + "] " + msg);
	}
	
	private static String timeStamp()
	{
		Date now = new Date();
		return now.toString();
	}
}
