#define INCLUDED_HOST_H

typedef struct Host{
    int type;
    char *name; 
    struct Host *id;
    unsigned int speed;
    char *Send;
    char *Receive;
    struct Router *address;
}Host;
