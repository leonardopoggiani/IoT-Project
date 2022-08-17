#include <stdio.h>
#include <stdlib.h>
#include "coap-engine.h"
#include "dev/leds.h"
#include "dev/button-sensor.h"
#include <time.h>
#include <../constants/constants.h>

#include "sys/log.h"
#define LOG_MODULE "App"
#define LOG_LEVEL LOG_LEVEL_APP


static void res_put_post_handler(coap_message_t *request, coap_message_t *response, uint8_t *buffer, uint16_t preferred_size, int32_t *offset);
static void get_landside_level_handler(coap_message_t *request, coap_message_t *response, uint8_t *buffer, uint16_t preferred_size, int32_t *offset);

static void landside_level_event_handler(void);

EVENT_RESOURCE(landside_level_sensor,
         "title=\"Landside level sensor;obs",
         get_landside_level_handler,
         res_put_post_handler,
         res_put_post_handler,
         NULL,
         landside_level_event_handler);


static double landside_level = 2.0;
static double old_landside_level = -1.0;
enum FloodingRisk{VERY_HIGH, HIGH, MEDIUM, LOW, DIS};
static enum FloodingRisk current_risk = LOW;
static bool discharging = false;

char json_response[512];

static void res_put_post_handler(coap_message_t *request, coap_message_t *response, uint8_t *buffer, uint16_t preferred_size, int32_t *offset)
{
    size_t len = 0;
    const uint8_t* payload = NULL;
    int success = 1;

    if((len = coap_get_payload(request, &payload))) 
    {
        if(success && strcmp((char*)payload, JSON_LEVEL_VERY_HIGH) == 0) {
			current_risk = VERY_HIGH;
            LOG_INFO("Level TOO high need to low down, FLOOD RISK! \n");
        } else if(success && strcmp((char*)payload, JSON_LEVEL_HIGH) == 0) {
			current_risk = HIGH;
            LOG_INFO("Level high need to low down, pay attention! \n");
        } else if(success && strcmp((char*)payload, JSON_LEVEL_MEDIUM) == 0) {
            current_risk = MEDIUM;
            LOG_INFO("Level is rising! \n");
        } else if(success && strcmp((char*)payload, JSON_LEVEL_LOW) == 0) {
        	current_risk = LOW;
            LOG_INFO("Level is too low! \n");
        } else if(success && strcmp((char*)payload, JSON_DISCHARGE_WATER) == 0) {
			discharging = true;
			current_risk = DIS;
			LOG_INFO("Discharging water! \n");
		}else if(success && strcmp((char*)payload, JSON_NORMAL) == 0) {
			discharging = false;
			LOG_INFO("Normal operativity! \n");
		}
        else {
            printf("ERROR: UNKNOWN COMMAND\n");
            printf("Command: %s", (char*)payload);
            success = 0;
        }
    }
    else{
        printf("ERROR: UNKNOWN COMMAND\n");
        printf("Command: %s", (char*)payload);
        success = 0;
    }
		
	if(!success) {
		coap_set_status_code(response, BAD_REQUEST_4_00);
	}
}

static void simulate_landside_level_change(){

	double variation = (double)(rand() % 5) / 15;
	
	old_landside_level = landside_level;
	int type = 0;

	type = rand()%100;
	if(discharging) {
		landside_level = landside_level - variation;

		int parteIntera = (int) landside_level;
		int parteDecimale = (int)((landside_level - parteIntera) * 10);
		printf("landside_level: %d.%d \n", parteIntera, parteDecimale);
	} else {
		if((rand()%100) < 40) {
			if(type >= 35)
				landside_level = landside_level + variation;
			else if(type < 20 )
				landside_level = landside_level - variation;

			int parteIntera = (int) landside_level;
			int parteDecimale = (int)((landside_level - parteIntera) * 10);
			printf("landside_level: %d.%d \n", parteIntera, parteDecimale);
		}	
	}
} 

static void get_landside_level_handler(coap_message_t *request, coap_message_t *response, uint8_t *buffer, uint16_t preferred_size, int32_t *offset)
{
	char message[30];
	int len;
	sprintf(message, "%g", landside_level);
	int parteIntera = (int) landside_level;
	int parteDecimale = (int)((landside_level - parteIntera) * 10);
	int parteInteraOld = (int) old_landside_level;
	int parteDecimaleOld = (int)((old_landside_level - parteInteraOld) * 10);
	sprintf(json_response, "{\"landside_level\": %d.%d, \"old_landside_level\": %d.%d}", parteIntera, parteDecimale, parteInteraOld, parteDecimaleOld);

	coap_set_header_content_format(response, APPLICATION_JSON);
	coap_set_header_etag(response, (uint8_t *)&len, 1);
	coap_set_payload(response, json_response, strlen(json_response));
}


static void landside_level_event_handler(void)
{
	simulate_landside_level_change();
 
	switch (current_risk) {
		case LOW:
			leds_single_off(LEDS_GREEN);
			leds_single_off(LEDS_RED);
			leds_on(LEDS_GREEN);
			break;
		case MEDIUM:
			leds_single_off(LEDS_GREEN);
			leds_single_off(LEDS_RED);
			leds_on(LEDS_GREEN);
		case HIGH:
			leds_single_off(LEDS_GREEN);
			leds_single_off(LEDS_RED);
			leds_on(LEDS_RED);		
			break;
		case VERY_HIGH:
			leds_single_off(LEDS_GREEN);
			leds_single_off(LEDS_RED);
			leds_on(LEDS_RED);
			break;
		case DIS:
			leds_single_off(LEDS_GREEN);
			leds_single_off(LEDS_RED);
			leds_on(LEDS_GREEN);
			leds_on(LEDS_RED);
			leds_single_off(LEDS_GREEN);
			leds_single_off(LEDS_RED);
			leds_on(LEDS_RED);
			leds_on(LEDS_GREEN);
			break;
	}

	if(old_landside_level != landside_level)
	{
		printf("There is a change, I'm going to notify it!\n");
  		coap_notify_observers(&landside_level_sensor);
	}
}