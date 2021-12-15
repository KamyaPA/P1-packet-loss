#define INCLUDED_HOST_H
#include "router.h"

typedef struct Host{
    int type; //Type is represented as an int. For Hosts, their type is 1.
    char *name; 
    struct Host *id;
    unsigned int speed;
    char *Send;
    char *Receive;
    struct Edge *address; //Hosts have an Edge to a router. Edge is in router.h
}Host;

