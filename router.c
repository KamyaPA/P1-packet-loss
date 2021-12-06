#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "hostOrRouter.h"
#include "router.h"
#include "host.h"


/*Prototype*/
void connect(void *r_one, void *r_two);


/*Functions*/
void connect(void *r_one, void *r_two){
    int n;

    /*Connecting two routers*/
    if(*((int*) r_one) == 2 && *((int*) r_two) == 2){
        /*Creates an array of pointers to connections*/
        ((Router*) r_one)->connections = (host_or_router*) malloc(n * sizeof(host_or_router)); 
        ((Router*) r_two)->connections = (host_or_router*) malloc(n * sizeof(host_or_router)); 

        /*adding pointers into array*/
        ((Router*) r_one)->connections[0].item = (void*) r_two;
        ((Router*) r_two)->connections[0].item = (void*) r_one; 
    }
    /*Connecting a router and a host*/
    else if(*((int*) r_one) == 1 && *((int*) r_two) == 2){
        /*Creates an array of pointers to connections*/
        ((Router*) r_two)->connections = (host_or_router*) malloc(n * sizeof(host_or_router)); 

        /*adding pointers into array*/
        ((Host*) r_one)->address = (Router*) r_two;
        ((Router*) r_two)->connections[0].item = (void*) r_one; 
    }
    /*Connecting a host and a router*/
    else if(*((int*) r_one) == 2 && *((int*) r_two) == 1){
        /*Creates an array of pointers to connections*/
        ((Router*) r_one)->connections = (host_or_router*) malloc(n * sizeof(host_or_router));  

        /*adding pointers into array*/
        ((Router*) r_one)->connections[0].item = (void*) r_two;
        ((Host*) r_two)->address = (Router*) r_one; 
    }
}



int routingtree_create(int n){
    int tree[n][n];
    for(int i = 0; i <= n; i++){
        for(int j = 0; j <= n; j++){
            tree[i][j] = 0;
        }
    }
    return tree;
}