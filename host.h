#define INCLUDED_HOST_H
<<<<<<< Updated upstream

typedef struct Host{
    int type;
=======
#include "router.h"

typedef struct Host{
    int type; //Type is represented as an int. For Hosts, their type is 1.
>>>>>>> Stashed changes
    char *name; 
    struct Host *id;
    unsigned int speed;
    char *Send;
    char *Receive;
<<<<<<< Updated upstream
    struct Router *address;
}Host;
=======
    struct Edge *address; //Hosts have an Edge to a router. Edge is in router.h
}Host;
>>>>>>> Stashed changes
