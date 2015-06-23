#include "sensorList.h"

void sensor_list_init(Sensor_list_t *sensor_list){

        sensor_list->size = 0;
        sensor_list->capacity = SENSOR_LIST_INITIAL_CAPACITY;

        // allocate memory for sensor_list->data
        sensor_list->data =(Value_list_t*)malloc(sizeof(Value_list_t) * sensor_list->capacity);
}



void value_list_init(Value_list_t *value_list){
	
	value_list->number_of_values = 0;
        value_list->capacity = VALUE_LIST_INITIAL_CAPACITY;

        // allocate memory for value_list->data
        value_list->data =(Value*)malloc(sizeof(Value) * value_list->capacity);



}


void sensor_list_double_capacity_if_full(Sensor_list_t *sensor_list) {

        if (sensor_list->size >= sensor_list->capacity) {

                // double sensor_list->capacity and resize the allocated memory accordingly
                sensor_list->capacity *= 2;
                sensor_list->data = realloc(sensor_list->data, sizeof(Value_list_t) * sensor_list->capacity);

        }
}


void value_list_double_capacity_if_full(Value_list_t *value_list){
	
	if (value_list->number_of_values >= value_list->capacity) {

                // double value_list->capacity and resize the allocated memory accordingly
                value_list->capacity *= 2;
                value_list->data = realloc(value_list->data, sizeof(Value) * value_list->capacity);

        }

}


Value_list_t sensor_list_get(Sensor_list_t *sensor_list, int index) {

        if (index >= sensor_list->size || index < 0) {
                printf("Index %d out of bounds for actuator_list of size %d\n", index, sensor_list->size);
                exit(1);
        }
        return sensor_list->data[index];

}


Value value_list_get(Value_list_t * value_list, int index){

	if (index >= value_list->number_of_values || index < 0) {
                printf("Index %d out of bounds for actuator_list of size %d\n", index, value_list->number_of_values);
                exit(1);
        }
        return value_list->data[index];

}



void sensor_list_append(Sensor_list_t *sensor_list, char* name, Value_list_t new_sensor) {

	int i;
        // make sure there's room to expand into
       	sensor_list_double_capacity_if_full(sensor_list);
        
	// append the value and increment sensor_list->size
        sensor_list->data[sensor_list->size].name = (char*)malloc(sizeof(char)*NAME_SIZE);
        strncpy(sensor_list->data[sensor_list->size].name, name, NAME_SIZE);
        value_list_init(sensor_list->data);
	for (i = 0 ; i < new_sensor.number_of_values ; i++)
		value_list_append(sensor_list->data, new_sensor.data[i]);
	sensor_list->size++;

}


void value_list_append(Value_list_t *value_list, Value new_value){
	
	// make sure there's room to expand into
        value_list_double_capacity_if_full(value_list);

        // append the value and increment value_list->size
        value_list->data[value_list->number_of_values].time = new_value.time;
        value_list->data[value_list->number_of_values].value = new_value.value;
        value_list->number_of_values++;

	

}


void sensor__list_free(Sensor_list_t *sensor_list) {

        free(sensor_list->data);

}

void value_list_free(Value_list_t *value_list) {

        free(value_list->data);

}


/*   Main for testing functions : 
int main(){

	Sensor_list_t sensor_list;
	Value_list_t value_list;
	sensor_list_init(&sensor_list);
	value_list_init(&value_list);
	char* nume_senzor = (char*)malloc(sizeof(char) * NAME_SIZE);

	Value old_value;
	old_value.time = 0;
	old_value.value = 3;

	value_list_append(&value_list, old_value);
	sensor_list_append(&sensor_list, nume_senzor, value_list);

	Value new_value;
	new_value.time = 0;
	new_value.value = 1;

	value_list_append(&value_list, new_value);
	new_value.value = 2; 
	value_list_append(&value_list, new_value);
	sensor_list_append(&sensor_list, nume_senzor, value_list);	
	int i,j ; 
	for (i= 0 ; i < sensor_list.size; i++){
		Value_list_t get_value;
		value_list_init(&get_value);
		get_value = sensor_list_get(&sensor_list, i);
		for (j = 0; j < get_value.number_of_values; j++){
			Value get;
			get = value_list_get(&get_value, j);
			printf("For sensor number %d, the %d value is : %lf\n", i, j, get.value);
		}
	}
 
	return 0;
}
*/
