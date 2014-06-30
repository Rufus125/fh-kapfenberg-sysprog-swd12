package at.fhj.swd;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.MalformedURLException;
import java.net.URL;
import java.net.URLConnection;

import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;
import org.json.simple.parser.ParseException;

public class Notifier {
	
	static String[] argsCopy =  new String[5];

	public static void main(String[] args) throws MalformedURLException, IOException, ParseException {
		
		final String buildUrl = System.getenv("BUILD_URL");
		BufferedReader in = connect(buildUrl);
		
		assignArgsCopyValues(args, buildUrl);

		String buildStatus = readBuildStatus(in);

		activateClient(argsCopy, buildStatus);

	}

	private static void assignArgsCopyValues(String[] args, String url) {
		argsCopy[0] = url;
		for(int i = 1; i < 4; ++i)
			argsCopy[i] = args[i -1];
	}
	
	private static BufferedReader connect(String buildUrl)
			throws MalformedURLException, IOException {
		URL oracle = new URL(buildUrl + "/api/json");
		URLConnection yc = oracle.openConnection();
		BufferedReader in = new BufferedReader(new InputStreamReader(
				yc.getInputStream()));
		return in;
	}

	private static String readBuildStatus(BufferedReader in)
			throws IOException, ParseException {
		String inputLine;
		String json = "";
		while ((inputLine = in.readLine()) != null)
			json = inputLine;
		in.close();
		String buildStatus = readJSON(json);
		return buildStatus;
	}

	private static void activateClient(String[] args, String buildStatus) {
		
		if (buildStatus.equals("FAILURE")) {
			argsCopy[4] = "on"; 
			AlarmClient.startClient(argsCopy);
			

		} else if (buildStatus.equals("SUCCESS")) {
			
			argsCopy[4] = "off";
			AlarmClient.startClient(argsCopy);
		}
	}

	private static String readJSON(String jsonString) throws ParseException {
		JSONParser parser = new JSONParser();
		Object obj = parser.parse(jsonString);
		JSONObject jsonObject = (JSONObject) obj;
		String result = (String) jsonObject.get("result");
		return result;

	}

}
