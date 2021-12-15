#define INCLUDED_HOST_H

typedef struct Host{
    int type; //Type is represented as an int. For Hosts, their type is 1.
    char *name; 
    struct Host *id;
    unsigned int speed;
    char *Send;
    char *Receive;
    struct Router *address; //Hosts are only connected to one Router. 
}Host;
