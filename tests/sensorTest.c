#include "/home/cristi/devicehub_dir/devicehub/src/sensorList.c"


int main(){

        Sensor_list_t sensor_list;
        Sensor_t sensor;
        sensor_list_init(&sensor_list);
        sensor_init(&sensor);
        char* nume_senzor = (char*)malloc(sizeof(char) * NAME_SIZE);

        Value_t old_value;
        old_value.time = 0;
        old_value.value = 3;

        sensor_append(&sensor, old_value);
        sensor_list_append(&sensor_list, nume_senzor, sensor);

        Value_t new_value;
        new_value.time = 0;
        new_value.value = 1;

        sensor_append(&sensor, new_value);
        new_value.value = 2; 
        sensor_append(&sensor, new_value);
        sensor_list_append(&sensor_list, nume_senzor, sensor);  
        int i,j ; 
        for (i= 0 ; i < sensor_list.size; i++){
                Sensor_t get_value;
                sensor_init(&get_value);
                get_value = sensor_list_get(&sensor_list, i);
                for (j = 0; j < get_value.number_of_values; j++){
                        Value_t get;
                        get = sensor_get(&get_value, j);
                        printf("For sensor number %d, the %d value is : %lf\n", i, j, get.value);
                }
        }
 
        return 0;
}
