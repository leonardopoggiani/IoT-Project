/* Takes from serial line the GREEN/YELLOW/RED command and then
turns on the GREEN/YELLOW/RED LEDs and turns off the others */

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
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(serial_line_test, ev, data)
{
	PROCESS_BEGIN();
	cc26xx_uart_set_input(serial_line_input_byte);
	serial_line_init();
	while(1){
		PROCESS_WAIT_EVENT_UNTIL(ev == serial_line_event_message);
		printf("received: %s\n", (char*)data);
		if(strcmp((char*)data,"GREEN") == 0) {
			printf("GREEN LED\n");
			leds_toggle(LEDS_GREEN);
			leds_off(LEDS_RED);
		} else if (strcmp((char*)data,"RED") == 0) {
			printf("RED LED\n");
			leds_toggle(LEDS_RED);
			leds_off(LEDS_GREEN);
		} else {
			printf("NEITHER RED OR GREEN\n");
			leds_off(LEDS_RED);
			leds_off(LEDS_GREEN);
		}

	}
	PROCESS_END();
}
