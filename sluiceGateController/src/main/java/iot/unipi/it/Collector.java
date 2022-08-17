package iot.unipi.it;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.SocketException;

import javax.swing.text.DefaultStyledDocument.ElementSpec;

import org.eclipse.californium.core.CoapServer;
import org.eclipse.paho.client.mqttv3.MqttException;

public class Collector extends CoapServer {
	private static final String[] requestsArray = {"Insert the target canal water level: ", "Insert the water level acceptable range: ",
													"Insert the target salinity values: ", "Insert the acceptable range for the salinity: "}; 

	public static void main(String[] args) throws MqttException, IOException {
		double salinity_target = 0;
		double water_level_landside_target = 0;
		int water_level_landside_acceptable_range = 0;
		int salinity_acceptable_range = 0;
		RegistrationServer rs = null;
		MqttClientCollector mqttClient = null;

		BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

		String command = "";
		String[] tokens;
		for(int i = 0; i < 4; i++){
			System.out.print(requestsArray[i]);
			command = reader.readLine();
			tokens = command.split(" ");
			if(i == 0)
				water_level_landside_target = Double.parseDouble(tokens[0]);
			else if(i == 1)
				water_level_landside_acceptable_range = Integer.parseInt(tokens[0]);
			else if(i == 2)
				salinity_target = Double.parseDouble(tokens[0]);
			else if(i == 3)
				salinity_acceptable_range = Integer.parseInt(tokens[0]);
			System.out.println();
		}

		mqttClient = new MqttClientCollector(salinity_target, salinity_acceptable_range);

		rs = new RegistrationServer(water_level_landside_target, water_level_landside_acceptable_range);
		rs.start();

		printCommands();

		while(true){
			command = reader.readLine();
			tokens = command.split(" ");
			String insertedCommand = tokens[0];
			if(insertedCommand.equals("!exit")){
				System.out.println("Bye bye");
				System.exit(1);
			}
			else if(insertedCommand.equals("!commands")){
				printCommands();
			}
			else if(insertedCommand.equals("!changeTargetLandsideLevel")){
				if(tokens.length < 2){
					System.out.println("Wrong command format");
					printCommandError();
					continue;
				}
				rs.changeTargetLevel(Double.parseDouble(tokens[1]));
				System.out.println("Target landside water level value changed succesfully");
			}
			else if(insertedCommand.equals("!changeAccLandsideLevel")){
				if(tokens.length < 2){
					System.out.println("Wrong command format");
					printCommandError();
					continue;
				}
				rs.changeAccLevel(Double.parseDouble(tokens[1]));
				System.out.println("Acceptable range for the landside water level value changed succesfully");
			}
			else if(insertedCommand.equals("!dischargeWater")){
				if(tokens.length < 1){
					System.out.println("Wrong command format");
					printCommandError();
					continue;
				}
				rs.dischargeWater();
				System.out.println("Water discharging");
			}
			else{
				printCommandError();
			}
		}
	}

	public static void printCommands(){
		System.out.println("\nCommand list:");
		System.out.println("!exit: exit the program");
		System.out.println("!commands: list possible commands");					
		System.out.println("!changeTargetLandsideLevel [new_value]: set new target landside water level value");
		System.out.println("!changeAccLandsideLevel [new_value]: set new acceptable range for the landside water level");
		System.out.println("!dischargeWater: discharge water to reduce level");
		System.out.println("\n");
	}

	public static void printCommandError(){
		System.out.println("The command cannot be recognised");
	}
}
