#include "sensorList.h"

void sensor_list_init(Sensor_list_t *sensor_list){

        sensor_list->size = 0;
        sensor_list->capacity = SENSOR_LIST_INITIAL_CAPACITY;

        // allocate memory for sensor_list->data
        sensor_list->data =(Sensor_t*)malloc(sizeof(Sensor_t) * sensor_list->capacity);
}



void sensor_init(Sensor_t *sensor){
	
	sensor->number_of_values = 0;
        sensor->capacity = SENSOR_INITIAL_CAPACITY;

        // allocate memory for sensor->data
        sensor->data =(Value_t*)malloc(sizeof(Value_t) * sensor->capacity);



}


void sensor_list_double_capacity_if_full(Sensor_list_t *sensor_list) {

        if (sensor_list->size >= sensor_list->capacity) {

                // double sensor_list->capacity and resize the allocated memory accordingly
                sensor_list->capacity *= 2;
                sensor_list->data = realloc(sensor_list->data, sizeof(Sensor_t) * sensor_list->capacity);

        }
}


void sensor_double_capacity_if_full(Sensor_t *sensor){
	
	if (sensor->number_of_values >= sensor->capacity) {

                // double sensor->capacity and resize the allocated memory accordingly
                sensor->capacity *= 2;
                sensor->data = realloc(sensor->data, sizeof(Value_t) * sensor->capacity);

        }

}


Sensor_t sensor_list_get(Sensor_list_t *sensor_list, int index) {

        if (index >= sensor_list->size || index < 0) {
                printf("Index %d out of bounds for sensor_list of size %d\n", index, sensor_list->size);
                exit(1);
        }
        return sensor_list->data[index];

}


Value_t sensor_get(Sensor_t * sensor, int index){

	if (index >= sensor->number_of_values || index < 0) {
                printf("Index %d out of bounds for value_list of size %d\n", index, sensor->number_of_values);
                exit(1);
        }
        return sensor->data[index];

}



void sensor_list_append(Sensor_list_t *sensor_list, char* name, Sensor_t new_sensor) {

	int i;
        // make sure there's room to expand into
       	sensor_list_double_capacity_if_full(sensor_list);
        
	// append the value and increment sensor_list->size
        sensor_list->data[sensor_list->size].name = (char*)malloc(sizeof(char)*NAME_SIZE);
        strncpy(sensor_list->data[sensor_list->size].name, name, NAME_SIZE);
        sensor_init(&sensor_list->data[sensor_list->size]);
	for (i = 0 ; i < new_sensor.number_of_values ; i++)
		sensor_append(&sensor_list->data[sensor_list->size], new_sensor.data[i]);
	sensor_list->size++;

}


void sensor_append(Sensor_t *sensor, Value_t new_value){
	
	// make sure there's room to expand into
        sensor_double_capacity_if_full(sensor);

        // append the value and increment sensor->size
        sensor->data[sensor->number_of_values].time = new_value.time;
        sensor->data[sensor->number_of_values].value = new_value.value;
        sensor->number_of_values++;

	

}


void sensor__list_free(Sensor_list_t *sensor_list) {

        free(sensor_list->data);

}

void sensor_free(Sensor_t *sensor) {

        free(sensor->data);

}



