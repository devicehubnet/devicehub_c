#include "actuatorList.h"

void actuator_list_init(Actuator_list_t *actuator_list){
	
	actuator_list->size = 0;
  	actuator_list->capacity = ACTUATOR_LIST_INITIAL_CAPACITY;

  	// allocate memory for actuator_list->data
	actuator_list->data =(Actuator*)malloc(sizeof(Actuator) * actuator_list->capacity);
}


void actuator_list_double_capacity_if_full(Actuator_list_t *actuator_list) {
	
	if (actuator_list->size >= actuator_list->capacity) {
    		
		// double actuator_list->capacity and resize the allocated memory accordingly
		actuator_list->capacity *= 2;
		actuator_list->data = realloc(actuator_list->data, sizeof(Actuator) * actuator_list->capacity);
  	
	}
}


Actuator actuator_list_get(Actuator_list_t *actuator_list, int index) {
	
	if (index >= actuator_list->size || index < 0) {
		printf("Index %d out of bounds for actuator_list of size %d\n", index, actuator_list->size);
    		exit(1);
  	}
  	return actuator_list->data[index];

}


void actuator_list_append(Actuator_list_t *actuator_list, char* name, Actuator new_actuator) {
  	
	// make sure there's room to expand into
  	actuator_list_double_capacity_if_full(actuator_list);

	// append the value and increment actuator_list->size
	actuator_list->data[actuator_list->size].name = (char*)malloc(sizeof(char)*NAME_SIZE);
	strncpy(actuator_list->data[actuator_list->size].name, name, NAME_SIZE);
	actuator_list->data[actuator_list->size].data = new_actuator.data;
	actuator_list->size++;

}


void actuator_list_free(Actuator_list_t *actuator_list) {
 
	free(actuator_list->data);	

}


