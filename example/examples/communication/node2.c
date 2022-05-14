//   • Node 3 and node 4 send UNICAST messages to node 1 every 5s. 

#include "contiki.h"
#include "net/netstack.h"
#include "net/nullnet/nullnet.h"
#include <string.h>
#include <stdio.h>
#include "sys/log.h"
#include "sys/etimer.h"

#define LOG_MODULE "App"
#define LOG_LEVEL LOG_LEVEL_INFO
#define SEND_INTERVAL (13 * CLOCK_SECOND)

static int uni_period = 0;

PROCESS(comm_proc, "unicast example");
AUTOSTART_PROCESSES(&comm_proc);

static void input_callback(const void *data, uint16_t len, const linkaddr_t *src, const linkaddr_t *dest){
	char received_data[strlen((char *)data) + 1];
	if(len == strlen((char *)data) + 1) {
		memcpy(& received_data, data, strlen((char *)data) + 1);
		LOG_INFO("TIMESTAMP: %lu, Received \"%s\", from ", clock_seconds(), received_data);
		LOG_INFO_LLADDR(src);
		LOG_INFO_("\n");
	}
}

PROCESS_THREAD(comm_proc, ev, data){
	static struct etimer periodic_timer;
	static char uni_msg[70];
	printf("nodeID: %d", linkaddr_node_addr.u8[0]);
	
	sprintf(uni_msg, "Hello, I am node %d and i am sending broadcast messages: \n", linkaddr_node_addr.u8[0]);
	PROCESS_BEGIN();

	/* Initialize NullNet */
	nullnet_buf = (uint8_t *)uni_msg;
	nullnet_set_input_callback(input_callback);

	etimer_set(&periodic_timer, SEND_INTERVAL);
	while(1) {
		PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&periodic_timer));
		LOG_INFO("TIMESTAMP: %lu, Sending BROADCAST (Leonardo)", clock_seconds());
		LOG_INFO_("\n");
		nullnet_len = strlen(uni_msg)+1;
		NETSTACK_NETWORK.output(NULL);
		uni_period += 8;
		etimer_reset(&periodic_timer);
	
	}
	
	PROCESS_END();
}


