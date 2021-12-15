#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "hostOrRouter.h"
#include "router.h"
#include "host.h"

#ifndef INCLUDED_LIST_H
#include "list.h"
#endif

/*Functions*/
void connect(void *r_one, void *r_two){
    /*Connecting two routers*/
    if(*((int*) r_one) == 2 && *((int*) r_two) == 2){
        /*Creates an array of pointers to connections*/ 

        /*adding pointers into array*/
        list_add(&(((Router*) r_one)->connections), r_two);
        list_add(&(((Router*) r_two)->connections), r_one); 
    }
    /*Connecting a router and a host*/
    else if(*((int*) r_one) == 1 && *((int*) r_two) == 2){
        /*Creates an array of pointers to connections*/

        /*adding pointers into array*/
        ((Host*) r_one)->address = (Router*) r_two;
        list_add(&(((Router*) r_two)->connections), r_one);
    }
    /*Connecting a host and a router*/
    else if(*((int*) r_one) == 2 && *((int*) r_two) == 1){
        /*Creates an array of pointers to connections*/
        /*adding pointers into array*/
        list_add(&(((Router*) r_one)->connections), r_two);
        ((Host*) r_two)->address = (Router*) r_one; 
    }
}
