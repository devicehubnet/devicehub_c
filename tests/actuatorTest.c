/* Tests for use of actuatorList.h */

#include "actuatorList.h"


int main() {

         // declare and initialize a new actuator_list
        Actuator_list_t actuator_list;
        actuator_list_init(&actuator_list);

         // fill it up with 150 arbitrary values
        // this should expand capacity up to 200
        Actuator actuator0; 
        actuator0.name = (char*)malloc(sizeof(char)* NAME_SIZE);
        strncpy(actuator0.name , "ceva", 5);
        actuator0.data = 0;
        actuator_list_append(&actuator_list, actuator0);
        free(actuator0.name);
        Actuator actuator1;
        actuator1.name = (char*)malloc(sizeof(char)*NAME_SIZE);
        strncpy(actuator1.name , "altceva", 10);
        actuator1.data = 1;
        actuator_list_append(&actuator_list, actuator1);
        // print out an arbitrary value in the actuator_list
        actuator0 = actuator_list_get(&actuator_list, 1);
        printf("Heres the value at 1: %s - %d \n", actuator1.name, actuator1.data);

        // we're all done playing with our actuator_list, 
        // so free its underlying data array
        actuator_list_free(&actuator_list);

}

