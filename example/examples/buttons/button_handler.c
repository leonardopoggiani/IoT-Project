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
		if(ev == button_hal_press_event) {
			btn = (button_hal_button_t *)data; 
			if(ev == button_hal_release_event) {
				btn = (button_hal_button_t *)data;
				printf("Release event (%s)\n", BUTTON_HAL_GET_DESCRIPTION(btn));
			}
			printf("Press event (%s)\n", BUTTON_HAL_GET_DESCRIPTION(btn));
		}
	}

	PROCESS_END();
}
