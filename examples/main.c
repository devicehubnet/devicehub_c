#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "devicehub.h"


#define API_KEY "df2fb3eb-aea5-4973-8c16-93610cf40a16"
#define PROJECT_ID 4571
#define DEVICE_ID "3b99279d-2352-40c0-9db9-2d661fb4c566"

int main(){

	devicehub_lib_init();
	devicehub_init(API_KEY, PROJECT_ID, DEVICE_ID);
	unsigned int port, keepalive;
	char* host;
	devicehub_connect(host, port, keepalive);
	devicehub_add_sensor("temperature", NUMERIC);
	devicehub_add_sensor("humidity", NUMERIC);

	devicehub_add_value("temperature", 2.0);
	devicehub_add_value("temperature", 4.2);
	devicehub_add_value("temperature", 5.6);

	devicehub_add_value("humidity", 4.3);
	devicehub_add_value("humidity", 2.1);
	devicehub_add_value("humidity", 2.3);
	devicehub_add_value("humidity", 4.5);

	// Publishing all the values memorated in sensor_list
	devicehub_send();
	
	// Listing the values memorated in some sensor
	devicehub_list_values("temperature");
	devicehub_list_values("humidity");

	
	// Giving values for actuator from subscribe
	devicehub_add_actuator("light");

	devicehub_disconnect();
}
