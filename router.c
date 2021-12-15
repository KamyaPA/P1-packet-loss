#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "router.h"
#include "host.h"

#ifndef INCLUDED_LIST_H
#include "list.h"
#endif



/*Prototype*/
void connect(void *r_one, void *r_two);


/*Function*/
void connect(void *r_one, void *r_two){

    //connects two routers.
    if(*((int*) r_one) == 2 && *((int*) r_two) == 2){
        //adds a pointer to each other in their connections list
        list_add(&(((Router*) r_one)->connections), r_two);
        list_add(&(((Router*) r_two)->connections), r_one); 
    }
    
    //connects a router and a host
    else if(*((int*) r_one) == 1 && *((int*) r_two) == 2){
        //adds a pointer to the host in the routers connections list, sets the hosts address to its router.
        ((Host*) r_one)->address = (Router*) r_two;
        list_add(&(((Router*) r_two)->connections), r_one);
    }

    //connects a host and a router. (The function doesnt care if you call connect(Host,Router) or connect(Router, Host))
    else if(*((int*) r_one) == 2 && *((int*) r_two) == 1){
        //adds a pointer to the host in the routers connections list, sets the hosts address to its router.
        list_add(&(((Router*) r_one)->connections), r_two);
        ((Host*) r_two)->address = (Router*) r_one; 
    }
}
