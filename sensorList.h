#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define SENSOR_LIST_INITIAL_CAPACITY 50
#define VALUE_LIST_INITIAL_CAPACITY 50
#define NAME_SIZE 20

typedef struct{
	float time;
        double value;
}Value;

typedef struct{
	char* name;
	int number_of_values;
	int capacity;
	Value* data;
}Value_list_t;


typedef struct {
  int size;      // slots used so far
  int capacity;  // total available slots
  Value_list_t* data;     // actuator list  we're storing
}Sensor_list_t;


enum sensorTypes{
        NUMERIC = 0,
        DIGITAL
};




void sensor_list_init(Sensor_list_t *sensor_list);
void value_list_init(Value_list_t *value_list);
void sensor_list_double_capacity_if_full(Sensor_list_t *sensor_list);
void value_list_double_capacity_if_full(Value_list_t *value_list);
Value_list_t sensor_list_get(Sensor_list_t *sensor_list, int index);
Value value_list_get(Value_list_t *value_list, int index);
void sensor_list_append(Sensor_list_t *sensor_list, char* name, Value_list_t new_actuator);
void value_list_append(Value_list_t *value_list, Value new_value);
void sensor_list_free(Sensor_list_t *sensor_list);
void value_list_free(Value_list_t *value_list);


