#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define ACTUATOR_LIST_INITIAL_CAPACITY 50
#define NAME_SIZE 20

typedef struct{
        char* name;
        int data;
} Actuator;

typedef struct {
  int size;      // slots used so far
  int capacity;  // total available slots
  Actuator* data;     // actuator list  we're storing
} Actuator_list_t;


void actuator_list_init(Actuator_list_t *actuator_list);
void actuator_list_double_capacity_if_full(Actuator_list_t *actuator_list);
Actuator actuator_list_get(Actuator_list_t *actuator_list, int index);
void actuator_list_append(Actuator_list_t *actuator_list, char* name, Actuator new_actuator);
void actuator_list_free(Actuator_list_t *actuator_list);
