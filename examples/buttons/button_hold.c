#include "contiki.h"
#include "os/dev/button-hal.h"
#include <stdio.h>
#include <string.h>

PROCESS(button_test, "test_button");
AUTOSTART_PROCESSES(&button_test);
PROCESS_THREAD(button_test, ev, data){
	button_hal_button_t *btn; 
	PROCESS_BEGIN();
	btn = button_hal_get_by_index(0); 
	printf("Device button count: %u.\n", button_hal_button_count);

	if(btn) { 
		printf("%s on pin %u with ID=0, Logic=%s, Pull=%s\n", BUTTON_HAL_GET_DESCRIPTION(btn), btn->pin, btn->negative_logic ? "Negative" : "Positive", btn->pull == GPIO_HAL_PIN_CFG_PULL_UP ? "Pull Up" : "Pull Down");
	}

	while(1) {
		PROCESS_YIELD();
		if(ev == button_hal_periodic_event) {
			btn = (button_hal_button_t *)data;
			printf("Periodic event, %u seconds \n", btn->press_duration_seconds);
			if(btn->press_duration_seconds > 5) {
				printf("Pressed for more than 5 secs. Do custom action\n");
			}
	       	}
	}

	PROCESS_END();
}
