#include "devicehub.h"

/**  MQTT FUNCTIONS START **/

MQTTClient client;
volatile MQTTClient_deliveryToken deliveredtoken;

int subscribed = 0;
int finished = 0;
int disc_finished = 0;


void actuator_callback(int state){

        actuator_list.data[actuator_list.size].data = state;
}


void delivered(void *context, MQTTClient_deliveryToken dt){
	printf("[PUBLISH] Message with token value %d delivery confirmed\n", dt);
	deliveredtoken = dt;
}


int msgarrvd(void *context, char *topicName, int topicLen, MQTTClient_message *message){

	int i;
	char* payloadptr;

	printf("[SUBSCRIBE] Message arrived\n");
	printf("		topic: %s\n", topicName);
	payloadptr = message->payload;
	
	//printf("[DEBUG] Message payload is : %s \n", payloadptr);


	char* token = strtok(payloadptr, ","); 
	token = strtok(NULL, ",");
	char* minitoken = strtok(token, ":");
	minitoken = strtok(NULL,":");
	int state =0 ;
	for(i = 0; i <= sizeof(minitoken) ; i++){
		if (minitoken[i] != '"' && minitoken[i] != ' ' && minitoken[i] != '\0'){
			state *= 10;
			state += minitoken[i] - '0' ;
		}
	
	}
	//printf("[DEBUG] State value is : %i \n", state);	
	actuator_callback(state);
	
	MQTTClient_freeMessage(&message);
	MQTTClient_free(topicName);
	return 1;
}


void connlost(void *context, char *cause){
	printf("\nConnection lost\n");
	printf("     cause: %s\n", cause);
}


void connecter(char *address, unsigned int keepalive){

	MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
	int rc;

	MQTTClient_create(&client, address, CLIENTID, MQTTCLIENT_PERSISTENCE_NONE, NULL);
	conn_opts.keepAliveInterval = (int)keepalive;
	conn_opts.cleansession = 1;

	MQTTClient_setCallbacks(client, NULL, connlost, msgarrvd, delivered);

	if ((rc = MQTTClient_connect(client, &conn_opts)) != MQTTCLIENT_SUCCESS){
		printf("Failed to connect, return code %d\n", rc);
		exit(-1);
	}

}


/**  MQTT FUNCTIONS END **/



void devicehub_lib_init(){

	
	sensor_list_init(&sensor_list);
	actuator_list_init(&actuator_list);
	api_key = (char*)malloc(sizeof(char) * NO_LETTERS);
	project_id = 0;
	device_id = (char*)malloc(sizeof(char) * NO_LETTERS);

 
}


int devicehub_init(char* api_key_value, int project_id_value, char* device_id_value){
	
	strncpy(api_key, api_key_value, sizeof(char)* NO_LETTERS);
	strncpy(device_id, device_id_value, sizeof(char) * NO_LETTERS);
	project_id = project_id_value;
	
	if (api_key == NULL || device_id == NULL)
		return INIT_FAILURE;
	return 0;

}


int devicehub_connect(char* hostname, unsigned int port, unsigned int keepalive){
	
	hostname = (char*)malloc(sizeof(char) * NAME_SIZE);
	char host[] = "mqtt.devicehub.net";
	strncpy(hostname, host, NAME_SIZE);
	port = 1883;
	keepalive = 60;
	char address[30];
	sprintf(address, "tcp://%s:%d", host, port);
	
	if (address == NULL)
		return INIT_FAILURE;

	connecter(address, keepalive);	
	return 0;

}

int devicehub_autoconfigure(){

	//TODO


}


int devicehub_send(){

	int i,j;
	char* topic;
	char* payload;
	MQTTClient_message pubmsg = MQTTClient_message_initializer;
	MQTTClient_deliveryToken token;
	

	for (i = 0 ; i < sensor_list.size; i++){
		for (j = 0 ; j < sensor_list.data[i].number_of_values; j++){
	
			topic = (char*)malloc(sizeof(char)*TOPIC_SIZE);
			sprintf(topic, "/a/%s/p/%d/d/%s/sensor/%s/data",api_key,project_id, device_id, sensor_list.data[i].name);
			payload = (char*)malloc(sizeof(char)*PAYLOAD_SIZE);
			sprintf(payload, "{\"value\":%lf}", sensor_list.data[i].data[j].value);
			pubmsg.payload = (void*)payload;
			pubmsg.payloadlen = strlen(payload);
			pubmsg.qos = QOS;
			pubmsg.retained = 0;
			
			MQTTClient_publishMessage(client, topic, &pubmsg, &token);

			while(deliveredtoken != token);
		}			
	}
	return 0;	
}


int devicehub_add_sensor(char* name, enum sensorTypes sensorType){

	Sensor_t sensor;
	sensor_init(&sensor);
	sensor_list_append(&sensor_list, name, sensor);
	
	if ( sensor_list.size == 0 ) 
		return ADD_FAILURE;
	
	return 0;
}


int devicehub_add_actuator(char* name){
	
	Actuator new_actuator;		
	actuator_list_append(&actuator_list, name, new_actuator);
	char* topic = (char*)malloc(sizeof(char) * TOPIC_SIZE);
	char* payload = (char*)malloc(sizeof(char)* PAYLOAD_SIZE);
	int ch;
	
	sprintf(topic, "/a/%s/p/%d/d/%s/actuator/%s/state",api_key,project_id, device_id, name);
	
	printf("[SUBSCRIBE] Close subscribe with \"Q\" or \"q\" \n");
	MQTTClient_subscribe(client, topic, QOS);	
	do {
        	ch = getchar();	
	} while( ch != 'Q' && ch != 'q');
	fclose (stdout);

	return 0;
}


int devicehub_add_value(char* name, double value){

	int i;
	Value_t new_value;
	new_value.time = 0;
	new_value.value = value;  
	for ( i = 0 ; i < sensor_list.size; i++ )
		if (!strncmp(sensor_list.data[i].name, name, NAME_SIZE)){
			sensor_append(&sensor_list.data[i], new_value);
			//printf("[DEBUG] the value given : %lf  --- the value resulted : %lf \n", 
			//	new_value.value, 
			//	sensor_list.data[i].data[sensor_list.data[i].number_of_values - 1].value);
			
		}
			
	
	return 0;
}



int devicehub_list_values(char* sensor_name){

	int i, j;
	for ( i = 0; i < sensor_list.size; i++){
		if ( !strncmp(sensor_list.data[i].name, sensor_name, NAME_SIZE) ){
			for( j = 0; j < sensor_list.data[i].number_of_values; j++){
				Value_t new_value;
				new_value = sensor_get(&sensor_list.data[i], j);
				printf("Value for %i index of  %s sensor is %lf\n", j, sensor_name, new_value.value);
			}
		}
	}
	return 0;
}


int devicehub_disconnect(){

	MQTTClient_disconnect(client, 10000);
	MQTTClient_destroy(&client);
	
		
}


