package iot.unipi.it;

import java.util.HashMap;
import java.util.Map;

import org.eclipse.californium.core.CoapClient;
import org.eclipse.californium.core.CoapHandler;
import org.eclipse.californium.core.CoapObserveRelation;
import org.eclipse.californium.core.CoapResponse;
import org.eclipse.californium.core.coap.CoAP.Code;
import org.eclipse.californium.core.coap.MediaTypeRegistry;
import org.eclipse.californium.core.coap.Request;

import iot.unipi.it.Utils;

public class CoapNetworkHandler{

	private final String JSON_LEVEL_VERY_HIGH = "{\"type\":\"level\", \"cause\": \"VERY_HIGH\"}";
	private final String JSON_LEVEL_HIGH = "{\"type\":\"level\", \"cause\": \"HIGH\"}";
	private final String JSON_LEVEL_MEDIUM = "{\"type\":\"level\", \"cause\": \"MEDIUM\"}";
	private final String JSON_LEVEL_LOW = "{\"type\":\"level\", \"cause\": \"LOW\"}";
	private final String JSON_DISCHARGE_WATER = "{\"type\":\"discharge\"}";
	private final String JSON_NORMAL = "{\"type\":\"normal\"}";

	private CoapClient client_LandsideLevelControllerSensor = null;
	private double level_target;
	private double acceptableRange;
	private String landsideLevelControllerAddress;
	private boolean dischargeWater = false;

	private static CoapNetworkHandler instance = null;

	public CoapNetworkHandler(double level_target, double acceptableRange){
		this.level_target = level_target;
		this.acceptableRange = acceptableRange;
		landsideLevelControllerAddress = null;
	}

    public static CoapNetworkHandler getInstance(double level_target, double acceptableRange) {
        if (instance == null)
            instance = new CoapNetworkHandler(level_target, acceptableRange);
        return instance;
	}

	public void addLandsideLevelController(String ipAddress){
		landsideLevelControllerAddress = ipAddress;
		client_LandsideLevelControllerSensor = new CoapClient("coap://[" + ipAddress + "]/landside_level_sensor");
		client_LandsideLevelControllerSensor.observe(
			new CoapHandler() {
				public void onLoad(CoapResponse response) {
					System.out.println("Response: " + response.getResponseText());
					if(!response.getResponseText().equals(""))
						handleLevelChange(response);
				}

				public void onError() {
					System.err.println("OBSERVING FAILED");
				}	
			}
		);
	}

	public void handleLevelChange(CoapResponse response){
		String responseText = response.getResponseText();
		Map<String, Object> jsonResponse = Utils.jsonParser(responseText);
		double new_levelValue = (Double)jsonResponse.get("landside_level");
		double old_levelValue = (Double)jsonResponse.get("old_landside_level");

		DbUtility.insertLevel(new_levelValue);
		String flood_risk = "";

		System.out.println("landsideLevel: " + new_levelValue + " [ " + (level_target - acceptableRange) + " - " + (level_target + acceptableRange) + " ] , old: " + old_levelValue);

		if(new_levelValue > level_target + acceptableRange){
			System.out.println("Level is too high");
			if(new_levelValue - old_levelValue >= 0.4) {
				// level is raising very fast, there may be a flood
				flood_risk = JSON_LEVEL_VERY_HIGH;
			} else {
				flood_risk = JSON_LEVEL_HIGH;
			}
			client_LandsideLevelControllerSensor.post(new CoapHandler() {
				public void onLoad(CoapResponse response) {
					if(response == null){
						System.out.println("POST error");
					}
				}

				public void onError() {
					System.err.println("OBSERVING FAILED");
				}	
			}, flood_risk, MediaTypeRegistry.APPLICATION_JSON);
		} else if(new_levelValue < level_target - acceptableRange) {
			System.out.println("Level is too low");
			flood_risk = JSON_LEVEL_LOW;
			client_LandsideLevelControllerSensor.post(new CoapHandler() {
				public void onLoad(CoapResponse response) {
					if(response == null){
						System.out.println("POST error");
					}
				}

				public void onError() {
					System.err.println("OBSERVING FAILED");
				}	
			}, JSON_LEVEL_LOW, MediaTypeRegistry.APPLICATION_JSON);
		} else {
			flood_risk = JSON_LEVEL_MEDIUM;
			System.out.println("Level is normal");
			client_LandsideLevelControllerSensor.post(new CoapHandler() {
				public void onLoad(CoapResponse response) {
					if(response == null){
						System.out.println("POST error");
					}
				}

				public void onError() {
					System.err.println("OBSERVING FAILED");
				}	
			}, flood_risk, MediaTypeRegistry.APPLICATION_JSON);
		}

		if(dischargeWater) {
			String opening = "";
			if(new_levelValue < level_target + acceptableRange) {
				opening =  JSON_NORMAL;
			} else {
				System.out.println("Need to discharge water from the canal, [OPEN]\n");
				opening = JSON_DISCHARGE_WATER;
			}

			client_LandsideLevelControllerSensor.post(new CoapHandler() {
				public void onLoad(CoapResponse response) {
					if(response == null){
						System.out.println("POST error");
					}
				}

				public void onError() {
					System.err.println("OBSERVING FAILED");
				}	
			}, opening, MediaTypeRegistry.APPLICATION_JSON);
		}
		
	}

	public void changeTargetLevel(double target){
		level_target = target;
	}

	public void changeAccLevel(double range){
		acceptableRange = range;
	}

	public void dischargeWater(){
		dischargeWater = true;
	}
}
