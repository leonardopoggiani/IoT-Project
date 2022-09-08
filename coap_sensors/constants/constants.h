#ifndef SENSOR_CONSTANTS_H
#define SENSOR_CONSTANTS_H

/* Servers constants */
#define SERVER_EP                                 "coap://[fd00::1]:5683"
#define CONNECTION_TRY_INTERVAL                   1
#define REGISTRATION_TRY_INTERVAL                 1
#define SIMULATION_INTERVAL                       1
#define CHECK_PERIOD                              CLOCK_SECOND
#define JSON_LEVEL	                              "{\"deviceType\":\"level_controller\"}"
#define SALINITY_SENSOR                           "salinity_sensor"

/* Oxygen sensor server constants */
#define JSON_LEVEL_VERY_HIGH                      "{\"type\":\"level\", \"cause\": \"VERY_HIGH\"}"
#define JSON_LEVEL_HIGH                           "{\"type\":\"level\", \"cause\": \"HIGH\"}"
#define JSON_LEVEL_MEDIUM                         "{\"type\":\"level\", \"cause\": \"MEDIUM\"}"
#define JSON_LEVEL_LOW                            "{\"type\":\"level\", \"cause\": \"LOW\"}"
#define JSON_DISCHARGE_WATER                      "{\"type\":\"discharge\"}"
#define JSON_NORMAL                               "{\"type\":\"normal\"}"


#endif /* SENSOR_CONSTANTS_H */