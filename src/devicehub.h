#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "sensorList.h"
#include "actuatorList.h"
#include "MQTTClient.h"

/* Error macros start */
#define ADD_FAILURE -1
#define INIT_FAILURE -2

/* Error macros end */


#define NO_LETTERS 50
#define CLIENTID    "testSub"
#define QOS         1
#define PAYLOAD_SIZE 50
#define TOPIC_SIZE 150


char* api_key;
int project_id; 
char* device_id;


Actuator_list_t actuator_list;
Sensor_list_t sensor_list;


typedef void (*function_actuator_callback)(int);


void devicehub_lib_init();
int devicehub_init(char* api_key_value, int project_id_value, char* device_id_value);
int devicehub_connect(char* hostname, unsigned int port, unsigned int keepalive);
int devicehub_autoconfigure();
int devicehub_send();
int devicehub_add_sensor(char* name, enum sensorTypes sensorType);
int devicehub_add_actuator(char* name );
int devicehub_add_value(char* name, double value);
int devicehub_list_values(char* sensor_name);
int devicehub_disconnect();


