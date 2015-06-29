#include "/home/cristi/devicehub_dir/devicehub/src/devicehub.c"


int main(){

        char* host = (char*)malloc(sizeof(char)* NAME_SIZE);
        unsigned int port;
        unsigned int keepalive;
        devicehub_lib_init();
        devicehub_init("dad", 123, "dadad");

        devicehub_connect(host, port, keepalive);
        
        char* name = (char*)malloc( sizeof(char)*NAME_SIZE );
        
        strncpy(name, "new_sensor", NAME_SIZE);
        Sensor_t new_values;
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

