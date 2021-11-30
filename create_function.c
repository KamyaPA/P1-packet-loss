#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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
    unsigned int speed;
    RoutingTree *tree;
    Queue queue;
} Router;

int main(void){}

// Speed, name and capacity(length of queue) will be input parameters along with a router struct

router_create(Router R, unsigned int speed_of_router, char *name_of_router, int length_of_queue){

R.name = *name_of_router;
R.id;
R.speed = speed_of_router;
R.tree = 
R.queue = 


}