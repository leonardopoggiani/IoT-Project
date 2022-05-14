#include "contiki.h"	
#include "net/netstack.h"
#include "net/nullnet/nullnet.h"
#include <string.h>
#include <stdio.h>
#include "sys/log.h"
#include "sys/etimer.h"

#define LOG_MODULE "App"
#define LOG_LEVEL LOG_LEVEL_INFO
#define SEND_INTERVAL (8 * CLOCK_SECOND)

/* 
   • Build a topology with 4 nodes
   • Node 3 and node 4 send UNICAST messages to node 1 every 5s. 
   • Node 2 send a BROADCAST message every 13s 
*/


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
	static char uni_msg[70];
	printf("nodeID: %d", linkaddr_node_addr.u8[0]);
	
	sprintf(uni_msg, "Hello, I am node 1 and i want to receive messages: \n");
	PROCESS_BEGIN();

	/* Initialize NullNet */
	nullnet_buf = (uint8_t *)uni_msg;
	nullnet_set_input_callback(input_callback);
	
	PROCESS_END();
}


