#include "os/dev/serial-line.h"
#include "arch/cpu/cc26x0-cc13x0/dev/cc26xx-uart.h"

PROCESS(serial_line_test, "Test serial line");
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
	}
	PROCESS_END();
}
