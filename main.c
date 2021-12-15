#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

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

#ifndef INCLUDED_TREE_H
    #include "tree.h"
#endif
int find_compare(const void * tree, const void * item);

int main(int argc, char *argv[]){
    double delay;
    Btree network = btree_create();
    Item *active;
    if(argc < 2){
        printf("To few arguments\n");
        return 0;
    }
    create_network(&network, argv[1]);

    printf("\n ===TEST_PRINT=== \n");
    if(btree_find(&network, (void *)"h_BottoamLeft", find_compare)){
        printf("FOUND\n");
    }
    else{
        printf("Does not exist\n");
    }
    run(network, 50);
}


int find_compare(const void * tree, const void * item){
    char *tree_name;
    tree_name = *(int *)tree == ROUTER ? ((Router *)tree)->name : ((Host *)tree)->name;
    return strcmp(tree_name, (char *)item);
}

void run(List network, int delay){
    int tick = 0;

    while(1){
        //Notes the time before the tick runs.
        time_t start,end;
        double dif;
        time (&start);

        //the functionality of the program.
        //loop_opjects(network, tick);
        
 
        //Notes the time after is run, calculates the difference in time between the beginning and end of the tick.
        time (&end);
        dif = difftime (end,start);

        //adds a delay so we can control the speed of the program without affecting traffic. 
        if(dif<(delay)/1000){
            sleep(delay/1000-dif);
        } 

        //adds 1 to the tick counter.
        tick++;
    }
}
/*
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
