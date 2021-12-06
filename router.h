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
    struct host_or_router *connections; /*Pointer to a collection of routers*/
    unsigned int speed;
    RoutingTree *tree;
    Queue queue;
} Router;