#include "contiki.h"
#include "sys/timer.h"
#include <stdio.h>
#include <string.h>

// Starting from t=0 and every 3 seconds, prints the number of 
// seconds elapsed (etimer)

PROCESS(timer_test, "test_timer");
AUTOSTART_PROCESSES(&timer_test);
PROCESS_THREAD(timer_test, ev, data){
	static struct etimer et;
	PROCESS_BEGIN();
	unsigned long t = 0;	

	etimer_set(&et, 3*CLOCK_SECOND);

	while(1) {
		PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
		printf("number of seconds elapsed: %lu \n", clock_seconds() - t);
		etimer_reset(&et);
	}

	PROCESS_END();
}

