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
    char *name;
    struct Router *id; /*Pointer to it self*/
    struct Router *connections; /*Pointer to a collection of routers*/
    unsigned int speed;
    RoutingTree *tree;
    Queue queue;
} Router;