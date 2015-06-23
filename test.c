#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "devicehub.h"


#define API_KEY "df2fb3eb-aea5-4973-8c16-93610cf40a16"
#define PROJECT_ID 4571
#define DEVICE_ID "3b99279d-2352-40c0-9db9-2d661fb4c566"

void actuator_callback(int state){

        actuator_list.data[actuator_list.size].data = state;
}



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
	devicehub_list_values("temperature");
	devicehub_send();
	function_actuator_callback actuator_callback;
	devicehub_add_actuator("bec",actuator_callback );

	devicehub_disconnect();
}
