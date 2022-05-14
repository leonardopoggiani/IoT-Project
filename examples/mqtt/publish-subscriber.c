#include "contiki.h"
#include "net/netstack.h"
#include "net/ipv6/simple-udp.h"
#include "mqtt.h"
/* Log configuration */
#include "sys/log.h"
#define LOG_MODULE "App"
#define LOG_LEVEL LOG_LEVEL_INFO
#define UDP_CLIENT_PORT 8765
#define UDP_SERVER_PORT 5678

// Data structure that stores the connection status
static struct mqtt_connection conn;
/* MQTT broker address. */
#define MQTT_CLIENT_BROKER_IP_ADDR "fd00::1"
static const char *broker_ip =
MQTT_CLIENT_BROKER_IP_ADDR;
// Default config values
#define DEFAULT_BROKER_PORT 1883
#define DEFAULT_PUBLISH_INTERVAL (30 * CLOCK_SECOND)
/* Maximum TCP segment size and length of IPv6 addresses
*/
#define MAX_TCP_SEGMENT_SIZE 32
#define CONFIG_IP_ADDR_STR_LEN 64

// Buffers for Client ID and Topics.
#define BUFFER_SIZE 64
// Application level buffer
#define APP_BUFFER_SIZE 512
static char app_buffer[APP_BUFFER_SIZE];

/* Various states */
static uint8_t state;
#define STATE_INIT 0 // Initial state
#define STATE_NET_OK 1 // Network is initialized
#define STATE_CONNECTING 2 // Connecting to MQTT broker
#define STATE_CONNECTED 3 // Connection successful
#define STATE_SUBSCRIBED 4 // Topics of interest subscribed
#define STATE_DISCONNECTED 5 // Disconnected from MQTT broker

static void mqtt_event(struct mqtt_connection *m, mqtt_event_t event, void *data)
{
	switch(event) {
		case MQTT_EVENT_CONNECTED: {
		// Connection completed
	}
	case MQTT_EVENT_DISCONNECTED: {
		// Disconnection occurred
	}
	case MQTT_EVENT_PUBLISH: {
		// Notification on a subscribed topic received
		// Data variable points to the MQTT message received
	}
	case MQTT_EVENT_SUBACK: {
		// Subscription successful
	}
	case MQTT_EVENT_UNSUBACK: {
		// Subscription canceled
	}

	case MQTT_EVENT_PUBACK: {
		// Publishing completed
	}
}

static bool have_connectivity(void)
{
	if(uip_ds6_get_global(ADDR_PREFERRED) == NULL || uip_ds6_defrt_choose() == NULL) {
		return false;
	}
	return true;
}

PROCESS_THREAD(contiki_ng_br, ev, data)
{
  PROCESS_BEGIN();

	printf("MQTT Client Process\n");
	// Initialize the ClientID as MAC address of the node
	snprintf(client_id, BUFFER_SIZE, "%02x%02x%02x%02x%02x%02x", linkaddr_node_addr.u8[0], linkaddr_node_addr.u8[1], linkaddr_node_addr.u8[2], linkaddr_node_addr.u8[5], linkaddr_node_addr.u8[6], linkaddr_node_addr.u8[7]);
	// Broker registration
	mqtt_register(&conn, &mqtt_client_process, client_id, mqtt_event, MAX_TCP_SEGMENT_SIZE); 
	state=STATE_INIT;

	// Initialize periodic timer to check the status
	etimer_set(&periodic_timer, STATE_MACHINE_PERIODIC);
	/* Main loop */
	while(1) {
	
		PROCESS_YIELD();
		if((ev == PROCESS_EVENT_TIMER && data == &periodic_timer) || ev == PROCESS_EVENT_POLL){
		// Manage the states
			if(state==STATE_INIT){
				if(have_connectivity()==true)
					state = STATE_NET_OK;
			}
			
			if(state == STATE_NET_OK){
			// Connect to MQTT server
				printf("Connecting!\n");
				memcpy(broker_address, broker_ip, strlen(broker_ip));
				mqtt_connect(&conn, broker_address, DEFAULT_BROKER_PORT, (DEFAULT_PUBLISH_INTERVAL * 3) / CLOCK_SECOND, MQTT_CLEAN_SESSION_ON);
				state = STATE_CONNECTING;
			}

			if(state==STATE_CONNECTED){
			// Subscribe to a topic
				strcpy(sub_topic,"actuator");
				status = mqtt_subscribe(&conn, NULL, sub_topic, MQTT_QOS_LEVEL_0);
				printf("Subscribing!\n");
				if(status == MQTT_STATUS_OUT_QUEUE_FULL) {
					LOG_ERR("Tried to subscribe but command queue was full!\n");
					PROCESS_EXIT();
				}
				state = STATE_SUBSCRIBED;
			}

			if(state == STATE_SUBSCRIBED){
				// Publish something
				sprintf(pub_topic, "%s", "status");
				sprintf(app_buffer, "report %d", value);
				value++;
				mqtt_publish(&conn, NULL, pub_topic,(uint8_t*) app_buffer,strlen(app_buffer),MQTT_QOS_LEVEL_0,MQTT_RETAIN_OFF);
			}
		
		}
	}

  PROCESS_END();
}




