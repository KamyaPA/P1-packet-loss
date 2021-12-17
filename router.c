#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "router.h"
#include "host.h"

#ifndef INCLUDED_LIST_H
#include "list.h"
#endif

#ifndef INCLUDED_CREATE_FUNCTION_H
#include "create_function.h"
#endif

#define GET_CONNECTION_LIST(X) &(((Router*) X)->connections)
#define GET_TYPE(X) *((int*) X)

/*Prototype*/
void connect(void *r_one, void *r_two, int length);

/*Functions*/

/*Create function for edges.*/
Edge create_edge(){
    Edge new;
    new.connection = NULL;
    new.length = 0;
    return new;
}

void connect(void *r1, void *r2, int length){
    //allocates memory for edges
    Edge *r_one = (Edge*) malloc (sizeof(Edge));
    Edge *r_two = (Edge*) malloc (sizeof(Edge));

    //Inserts the function inputs into the edges
    r_one->connection = r1;
    r_one->length = length;
    
    r_two->connection = r2;
    r_two->length = length;


    //connects two routers.
    if(GET_TYPE(r1) == ROUTER && GET_TYPE(r2) == ROUTER){
        //adds a pointer to each other in their connections list
        list_add(GET_CONNECTION_LIST(r1), r_two);
        list_add(GET_CONNECTION_LIST(r2), r_one); 
    }
    
    //connects a router and a host
    else if(GET_TYPE(r1) == HOST && GET_TYPE(r2) == ROUTER){
        //adds a pointer to the host in the routers connections list, sets the hosts address to its router.
        ((Host*) r1)->address = r_two;
        list_add(GET_CONNECTION_LIST(r2), r_one);
    }

    //connects a host and a router. (The function doesnt care if you call connect(Host,Router) or connect(Router, Host))
    else if(GET_TYPE(r1) == ROUTER && GET_TYPE(r2) == HOST){
        //adds a pointer to the host in the routers connections list, sets the hosts address to its router.
        list_add(GET_CONNECTION_LIST(r1), r_two);
        ((Host*) r2)->address = r_one; 
    }
}
