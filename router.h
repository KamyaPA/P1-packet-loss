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
    struct Router *id; /*Pointer to it self*/
    struct List connections; /*Pointer to a collection of routers*/
    unsigned int speed;
    RoutingTree *tree;
    Queue queue;
} Router;