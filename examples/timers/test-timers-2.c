#include "contiki.h"
#include "sys/ctimer.h"
#include <stdio.h>
#include <string.h>

// Every 10 seconds calls a function that prints “x seconds are gone”, 
// were x is incremented each time by 10 (ctimer)

PROCESS(timer_test, "test_timer");
AUTOSTART_PROCESSES(&timer_test);
static struct ctimer ct;
unsigned long x = 0;

static void callback(void* ptr) {
	x += 10;
	printf("x seconds are gone: %lu \n", x);
	ctimer_reset(&ct);
}

PROCESS_THREAD(timer_test, ev, data){

	PROCESS_BEGIN();

	ctimer_set(&ct, 10*CLOCK_SECOND, callback, NULL);

	PROCESS_END();
}

