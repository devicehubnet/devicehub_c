#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define SENSOR_LIST_INITIAL_CAPACITY 50
#define SENSOR_INITIAL_CAPACITY 50
#define NAME_SIZE 20

typedef struct{
	float time;
        double value;
}Value_t;


typedef struct{
	char* name;
	int number_of_values; //values used so far
	int capacity; // total available slots for values
	Value_t* data; // values list we're storing
}Sensor_t;


typedef struct {
  int size;      // slots used so far
  int capacity;  // total available slots
  Sensor_t* data;     // actuator list  we're storing
}Sensor_list_t;


enum sensorTypes{
        NUMERIC = 0,
        DIGITAL
};




void sensor_list_init(Sensor_list_t *sensor_list);
void sensor_init(Sensor_t *sensor);
void sensor_list_double_capacity_if_full(Sensor_list_t *sensor_list);
void sensor_double_capacity_if_full(Sensor_t *sensor);
Sensor_t sensor_list_get(Sensor_list_t *sensor_list, int index);
Value_t sensor_get(Sensor_t *sensor, int index);
void sensor_list_append(Sensor_list_t *sensor_list, char* name, Sensor_t new_sensor);
void sensor_append(Sensor_t *sensor, Value_t new_value);
void sensor_list_free(Sensor_list_t *sensor_list);
void sensor_free(Sensor_t *sensor);


