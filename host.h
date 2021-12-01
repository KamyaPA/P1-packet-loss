#include "router.h"
typedef struct Host{
    char *name; 
    struct Host *id;
    unsigned int speed;
    char *Send;
    char *Receive;
    struct Router *address;
}Host;