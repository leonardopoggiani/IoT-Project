#include "os/dev/serial-line.h"

PROCESS(serial_line_test, "Test serial line");
AUTOSTART_PROCESSES(&serial_line_test);
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(serial_line_test, ev, data)
{
	PROCESS_BEGIN();
	while(1){
		PROCESS_WAIT_EVENT_UNTIL(ev == serial_line_event_message);
		printf("received: %s\n", (char*)data);
	}

	PROCESS_END();
}
