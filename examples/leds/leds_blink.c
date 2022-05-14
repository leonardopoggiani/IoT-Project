/* Makes all LEDs blink (turn on and off) with a period of two seconds */
#include "os/dev/serial-line.h"
#include "arch/cpu/cc26x0-cc13x0/dev/cc26xx-uart.h"
#include "contiki.h"
#include "net/netstack.h"
#include "os/dev/leds.h"
#include <stdio.h>
#include <string.h>
#include "sys/ctimer.h"

PROCESS(serial_line_test, "Serial line leds");
AUTOSTART_PROCESSES(&serial_line_test);
static struct ctimer b_leds;

void blink_callback(){
	leds_toggle(LEDS_GREEN);
	leds_toggle(LEDS_RED);
	ctimer_set(&b_leds, 1*CLOCK_SECOND,blink_callback,NULL);
	return;
}

/*---------------------------------------------------------------------------*/
PROCESS_THREAD(serial_line_test, ev, data)
{
	PROCESS_BEGIN();
	
	ctimer_set(&b_leds, 2*CLOCK_SECOND,blink_callback,NULL);

	PROCESS_END();
}
