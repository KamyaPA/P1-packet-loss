typedef struct Host{
    char *name; 
    struct Host *id;
    unsigned int speed;
    char *Send;
    char *Receive;
    Router *address;
}Host;