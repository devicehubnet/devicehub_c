#include "devicehub.h"


/**  MQTT FUNCTIONS START **/

MQTTClient client;
volatile MQTTClient_deliveryToken deliveredtoken;

int subscribed = 0;
int finished = 0;
int disc_finished = 0;


void delivered(void *context, MQTTClient_deliveryToken dt){
	printf("Message with token value %d delivery confirmed\n", dt);
	deliveredtoken = dt;
}


int msgarrvd(void *context, char *topicName, int topicLen, MQTTClient_message *message){

	int i;
	char* payloadptr;

	printf("Message arrived\n");
	printf("     topic: %s\n", topicName);
	payloadptr = message->payload;
	

	char* token = strtok(payloadptr, ","); 
	token = strtok(NULL, ",");
	char* minitoken = strtok(token, ":");
	minitoken = strtok(NULL,":");
	int state =0 ;
	for(i = 2; i < sizeof(minitoken) ; i++){
		state*=10;
		state += minitoken[i] - '0' ;
	}	
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

			/*printf("Waiting for publication of %s\n"
				"on topic %s for client with ClientID: %s\n",
				payload, topic, CLIENTID);	
			*/
			while(deliveredtoken != token);
		}			
	}
	return 0;	
}


int devicehub_add_sensor(char* name, enum sensorTypes sensorType){

	Value_list_t values;
	value_list_init(&values);
	sensor_list_append(&sensor_list, name, values);
	
	if ( sensor_list.size == 0 ) 
		return ADD_FAILURE;
	
	return 0;
}


int devicehub_add_actuator(char* name, function_actuator_callback actuator_callback){
	
	//TODO 
	Actuator new_actuator;		
	actuator_list_append(&actuator_list, name, new_actuator);
	char* topic = (char*)malloc(sizeof(char) * TOPIC_SIZE);
	char* payload = (char*)malloc(sizeof(char)* PAYLOAD_SIZE);
	int ch;
	
	sprintf(topic, "/a/%s/p/%d/d/%s/actuator/%s/state",api_key,project_id, device_id, name);
	
	MQTTClient_subscribe(client, topic, QOS);	
	do 
    	{
        	ch = getchar();
		
		//freopen ("myfile.txt","w",stdin);
		//actuator_callback(state);
    	
	} while( ch != 'Q' && ch != 'q');
	fclose (stdout);

	return 0;
}


int devicehub_add_value(char* name, double value){

	int i;
	Value new_value;
	new_value.time = 0;
	new_value.value = value;  
	for ( i = 0 ; i < sensor_list.size; i++ )
		if (!strncmp(sensor_list.data[i].name, name, NAME_SIZE))
			value_list_append(&sensor_list.data[i], new_value);
		else 
			return ADD_FAILURE;
	
	return 0;
}



int devicehub_list_values(char* sensor_name){

	int i, j;
	Value new_value;
	for ( i = 0; i < sensor_list.size; i++){
		if ( !strncmp(sensor_list.data[i].name, sensor_name, NAME_SIZE) )
			for( j = 0; j < sensor_list.data[i].number_of_values; j++){
				new_value = value_list_get(sensor_list.data, j);
				printf("Value for %i index is %lf\n", j, new_value.value);
			}
	}
	return 0;
}


int devicehub_disconnect(){

	MQTTClient_disconnect(client, 10000);
	MQTTClient_destroy(&client);
	
		
}

/* Main for tests:

int main(){

	char* host = (char*)malloc(sizeof(char)* NAME_SIZE);
	unsigned int port;
	unsigned int keepalive;
	devicehub_lib_init();
	devicehub_init("dad", 123, "dadad");

	devicehub_connect(host, port, keepalive);
	
	char* name = (char*)malloc( sizeof(char)*NAME_SIZE );
	
	strncpy(name, "new_sensor", NAME_SIZE);
	Value_list_t new_values;
	enum sensorTypes type;
	devicehub_add_sensor("new_sensor", type);
	int n = 0 ;
	devicehub_add_value(name, n);
	devicehub_add_value(name, n+1);
	devicehub_add_value(name, n+2);
	devicehub_list_values(name);
	devicehub_send();
	devicehub_disconnect();		
	return 0;	

}

*/
