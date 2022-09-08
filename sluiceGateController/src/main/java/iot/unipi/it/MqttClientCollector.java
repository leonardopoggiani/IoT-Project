package iot.unipi.it;

import java.util.HashMap;
import java.util.Map;

import org.eclipse.paho.client.mqttv3.IMqttDeliveryToken;
import org.eclipse.paho.client.mqttv3.MqttCallback;
import org.eclipse.paho.client.mqttv3.MqttClient;
import org.eclipse.paho.client.mqttv3.MqttException;
import org.eclipse.paho.client.mqttv3.MqttMessage;

import iot.unipi.it.Utils;

public class MqttClientCollector implements MqttCallback{

	private final String brokerAddr = "tcp://127.0.0.1:1883";
	private final String clientId = "Java_MqttClient";

	private final String JSON_GATE_OPEN = "{\"sluice_on\":true}";
	private final String JSON_GATE_CLOSED = "{\"sluice_on\":false}";

	private final String subTopic = "current_salinity";
	private final String pubTopic = "sluice_state"; 

	private MqttClient mqttClient = null;

	private double targetSalinity = 0.0;
	private double firstSalinityValue = 0;
	private int acceptableRange = 0;

	public MqttClientCollector(double targetSalinity, int acceptableRange){
		this.targetSalinity = targetSalinity;
		this.acceptableRange = acceptableRange;

		do{
			try{
				mqttClient = new MqttClient(brokerAddr, clientId);
				System.out.println("Connecting to the broker " + brokerAddr);
				mqttClient.setCallback(this);
				mqttClient.connect();
				System.out.println("Connection to the broker successful");
				mqttClient.subscribe(subTopic);
				System.out.println("Application correctly subscribed to the topic " + subTopic);
			} catch(MqttException e){
				System.out.println("Not able to connect. Retrying...");
			}
		} while (!mqttClient.isConnected());
	}

	public void connectionLost(Throwable cause) {
		System.out.println("Connection is broken: " + cause);
		int timeWindow = 3000;
		while (!mqttClient.isConnected()) {
			try {
				System.out.println("Trying to reconnect in " + timeWindow/1000 + " seconds.");
				Thread.sleep(timeWindow);
				System.out.println("Reconnecting ...");
				timeWindow *= 2;
				mqttClient.connect();
				
				mqttClient.subscribe(subTopic);
				System.out.println("Connection is restored");
			}catch(MqttException me) {
				System.out.println("Connection problems..");
			} catch (InterruptedException e) {
				System.out.println("Connection problems..");
			}
		}
	}

	public void messageArrived(String topic, MqttMessage message) throws Exception {
		System.out.println("A new message at the topic " + topic + " has been received");
		String receivedPayload = new String(message.getPayload());
		Map<String, Object> receivedJson = Utils.jsonParser(receivedPayload);
		String receivedSalinity_string = (String)receivedJson.get("current_salinity");

		double receivedSalinity = Double.parseDouble(receivedSalinity_string);
		System.out.println("[MQTTClientCollector] receivedSalinity: " + receivedSalinity);

		Boolean receivedState = (Boolean)receivedJson.get("sluice_state");
		System.out.println("[MQTTClientCollector] receivedSluiceState: " + receivedState);

		if(firstSalinityValue == 0){
			firstSalinityValue = receivedSalinity;
		}
		else {
			double averageSalinity = (firstSalinityValue + receivedSalinity) / 2;
			DbUtility.insertSalinity(averageSalinity);
			if(averageSalinity >= targetSalinity + acceptableRange){
				System.out.println("[MQTTClientCollector] Salinity level is too high, need to decrease it");
				publish(pubTopic, JSON_GATE_CLOSED);
			}
			else if(averageSalinity < targetSalinity - acceptableRange){
				System.out.println("[MQTTClientCollector] Salinity level is too low, need to increase it");
				publish(pubTopic, JSON_GATE_OPEN);
			}
			firstSalinityValue = 0;
		}
	}

	public void deliveryComplete(IMqttDeliveryToken token) {
		System.out.println("Delivery of the message correctly completed");			
	}

	public void publish(final String topic, final String content){
		try {
			MqttMessage message = new MqttMessage(content.getBytes());
			mqttClient.publish(topic, message);
			System.out.println("New message published succesfully to the topic " + topic + ". Message = " + content);
		} catch(MqttException me) {
			me.printStackTrace();
		}
	}
	
	public void changeTargetSalinity(int salinity){
		targetSalinity = salinity;
	}
}
