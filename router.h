#define INCLUDED_ROUTER_H

#ifndef INCLUDED_LIST_H
    #include "list.h"
#endif

#ifndef INCLUDED_ROUTINGTREE_H
    #include "routing_tree.h"
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
    RtreeItem *routing_tree;
    Queue queue;
} Router;

typedef struct Edge{
    int length;
    void *connection;
}Edge;

/*Prototype*/
void connect_objects(void *r_one, void *r_two, int length);
