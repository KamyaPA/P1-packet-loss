#define INCLUDED_ROUTER_H

#ifndef INCLUDED_LIST_H
    #include "list.h"
#endif

typedef struct RoutingTree{
    int i;
}RoutingTree;

typedef struct Queue{
    int length;
    char *start;
    char *read;
    char *write;
} Queue;

typedef struct Router{
    int type; 
    char *name;
    struct Router *id; //Pointer to itself
    struct List connections; //List of connections
    unsigned int speed;
    RoutingTree *tree;
    Queue queue;
} Router;