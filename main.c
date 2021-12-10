#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#ifndef INCLUDED_CONF_H
#include "conf.h"
#endif

#ifndef INCLUDED_LIST_H
#include "list.h"
#endif

#ifndef INCLUDED_ROUTER_H
    #include "router.h"
#endif

#ifndef INCLUDED_HOST_H
    #include "host.h"
#endif

#ifndef INCLUDED_CREATE_FUNCTION_H
    #include "create_function.h"
#endif

int main(int argc, char *argv[]){
    List network;
    Item *active;
    if(argc < 1){
        printf("To few arguments");
        return 0;
    }
    create_network(&network, argv[1]);
    
    printf("\n ===TEST_PRINT=== \n");
    active = network.first;
    while(active->next != NULL){
        if(*(int*)(active->item) == ROUTER)
            printf("Router: Name = \"%s\"\n", ((Router *)(active->item))->name);
        else if(*(int*)(active->item) == HOST)
            printf("Router: Name = \"%s\"\n", ((Host *)(active->item))->name);
        active = active->next;   
    }
}
/*
void run(List *network){
    int tick = 0;
    do{
        loop_opjects(network, tick);
        tick++;
        /*Add delay
    }while(1)
}

loop_opjects(List *network, int tick){
    void *active = network->first;
    while(active != NULL){
        if(*(int*)active == 1){
            action_router((Router *)active), tick);
        }
        else(
            action_host((Host *)active), tick);
        )
    }
}

void action_router(Router *R, int tick){
    if(!(tick % R->speed)){
        router_send_packet(R);
    }
}

void action_host(Host *H, int tick){
    if(!(tick % H->speed)){
        host_send_packet(H);
    }
}
*/
