package iot.unipi.it;

import java.net.SocketException;
import java.nio.charset.StandardCharsets;
import java.util.Map;

import org.eclipse.californium.core.CoapResource;
import org.eclipse.californium.core.CoapServer;
import org.eclipse.californium.core.coap.CoAP.ResponseCode;
import org.eclipse.californium.core.server.resources.CoapExchange;

import iot.unipi.it.Utils;

public class RegistrationServer extends CoapServer {
	private static CoapNetworkHandler coapHandler;
	
	public RegistrationServer(double water_level_landside_target, double acceptableRange) throws SocketException {
        this.add(new RegistrationResource());
		coapHandler = CoapNetworkHandler.getInstance(water_level_landside_target, acceptableRange);
    }
	
	class RegistrationResource extends CoapResource{
		public RegistrationResource(){
			super("registration");
		}

		@Override
		public void handlePOST(CoapExchange exchange){
			String requestText = exchange.getRequestText();
			Map<String, Object> jsonObject = Utils.jsonParser(requestText);
			String deviceType = (String) jsonObject.get("deviceType");
			System.out.println("Incoming device type " + deviceType);
			String ipAddress = exchange.getSourceAddress().getHostAddress();

            if(deviceType.equals("level_controller"))
                coapHandler.addLandsideLevelController(ipAddress);

			exchange.respond(ResponseCode.CREATED, "Registration completed!".getBytes(StandardCharsets.UTF_8));
		}
	}

	public void changeTargetLevel(double target){
		coapHandler.changeTargetLevel(target);
	}

	public void changeAccLevel(double range){
		coapHandler.changeAccLevel(range);
	}

	public void dischargeWater(){
		coapHandler.dischargeWater();
	}
}
