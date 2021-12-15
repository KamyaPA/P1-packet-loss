#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "hostOrRouter.h"
#include "router.h"
#include "host.h"
<<<<<<< Updated upstream

#ifndef INCLUDED_LIST_H
#include "list.h"
#endif


/*Prototype*/
void connect(void *r_one, void *r_two);
=======

#ifndef INCLUDED_LIST_H
#include "list.h"
#endif
#define GET_CONNECTION_LIST(X) &(((Router*) X)->connections)
#define GET_TYPE(X) *((int*) X)
>>>>>>> Stashed changes

/*Prototype*/
void connect(void *r_one, void *r_two, int length);

/*Functions*/
<<<<<<< Updated upstream
void connect(void *r_one, void *r_two){
    int n;

    /*Connecting two routers*/
    if(*((int*) r_one) == 2 && *((int*) r_two) == 2){
        /*Creates an array of pointers to connections*/
        void *p1 =  malloc(sizeof(void*)); 
        void *p2 =  malloc(sizeof(void*));

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
=======

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
    if(GET_TYPE(r1) == 2 && GET_TYPE(r2) == 2){
        //adds a pointer to each other in their connections list
        list_add(GET_CONNECTION_LIST(r1), r_two);
        list_add(GET_CONNECTION_LIST(r2), r_one); 
    }
    
    //connects a router and a host
    else if(GET_TYPE(r1) == 1 && GET_TYPE(r2) == 2){
        //adds a pointer to the host in the routers connections list, sets the hosts address to its router.
        ((Host*) r_one)->address = (Edge*) r_two;
        list_add(GET_CONNECTION_LIST(r2), r_one);
    }

    //connects a host and a router. (The function doesnt care if you call connect(Host,Router) or connect(Router, Host))
    else if(GET_TYPE(r1) == 2 && GET_TYPE(r2) == 1){
        //adds a pointer to the host in the routers connections list, sets the hosts address to its router.
        list_add(GET_CONNECTION_LIST(r1), r_two);
        ((Host*) r_two)->address = (Edge*) r_one; 
>>>>>>> Stashed changes
    }
}