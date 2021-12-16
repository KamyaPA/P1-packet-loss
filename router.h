#define INCLUDED_ROUTER_H

#ifndef INCLUDED_LIST_H
    #include "list.h"
#endif


typedef struct Queue{
    int length;
    char *start;
    char *read;
    char *write;
} Queue;

typedef struct Router{
    int type; //type of router is represented as an int. For routers, their type is 2.
    char *name;
    struct Router *id; //Pointer to itself
    struct List connections; //List of connections
    unsigned int speed;
    /*RoutingTree *tree;*/
    Queue queue;
} Router;

typedef struct Edge{
    int length;
    void *connection;
}Edge;

/*Prototype*/
void connect(void *r_one, void *r_two, int length);
