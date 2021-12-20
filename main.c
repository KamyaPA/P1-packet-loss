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

#ifndef INCLUDED_PACKET_H
    #include "packet.h"
#endif
#include "packet_to_queue.h"

#define PACKET_REACHED_DESTINATION 2

int find_compare(const void * tree, const void * item);
void run(Btree *network, int delay, int max_tick, char *output, int output_rate);
int loop_opjects(Btree *network, List *all_hosts, int tick);
int action_router(Router *source);
int action_host(Host *source, List *all_hosts);
void get_hosts(Btree *network, List *hosts);

/* argv[1] config-file,
 * argv[2] output-file
 * argv[3] hwo many ticks
 * argv[4] ouput how often
 */
int main(int argc, char *argv[]){ 
    /*double delay;*/
    Btree network = btree_create();
    /*Item *active;*/
    if(argc < 5){
        printf("To few arguments\n");
        return 0;
    }
    srand(time(NULL));
    create_network(&network, argv[1]);
    run(&network, 0, atoi(argv[3]), argv[2], atoi(argv[4]));
}



void run(Btree *network, int delay, int max_tick, char *output, int output_rate){
    FILE *output_file = fopen(output, "w");
    int tick = 1;
    int packet_loss = 0;
    List all_hosts;
    get_hosts(network, &all_hosts);

    if(output_file == NULL){
        printf("Couldn't open file %s", output);
        exit(1);
    }

    while(tick <= max_tick){
        //Notes the time before the tick runs.
        /*time_t start,end;
        double dif;
        time (&start);*/

        //the functionality of the program.
        packet_loss += loop_opjects(network, &all_hosts, tick);        
 
        //Notes the time after is run, calculates the difference in time between the beginning and end of the tick.
        /*time (&end);
        dif = difftime (end,start);

        //adds a delay so we can control the speed of the program without affecting traffic. 
        if(dif < ((double)delay) / 1000){
            sleep((double)delay / 1000 - dif);
        }*/

        //adds 1 to the tick counter.
        if(tick % output_rate == 0){
            fprintf(output_file, "%d %d\n", tick, packet_loss);
            packet_loss = 0;
        }
        tick++;
    }
    fclose(output_file);
}

void get_hosts(Btree *network, List *hosts){
    if(network != NULL){
        if(*(int *)network->item == HOST){
            list_add(hosts,(void *)(((Host *)(network->item))->id));
        }
        get_hosts(network->greater, hosts);
        get_hosts(network->smaller, hosts);
    }
}

int action_router(Router *source){
    void *destination;
    int i;
    int result = 1;
    /*Is the queue empty*/
    if(source->queue.read != source->queue.write){
        PacketHeader header;
        char *read = source->queue.read;
        for(i = 0; i < sizeof(PacketHeader); i++){
            ((char *)&header)[i] = *(read++);
            if(read - source->queue.start > source->queue.length){
                read = source->queue.start;
            }
        }
        /*Get destination*/
        destination = header.destination_address;
        /*Find next spot*/
        while(1){
            for(i = 0; source->routing_tree[i].node != destination; i++);
            if((void *) source == source->routing_tree[i].node_before){
                break;
            }
            else{
                destination = source->routing_tree[i].node_before;
            }
        }
        /*Send a packet*/

        if(*(int *)destination == HOST){
            /*Router to host*/
            send_to_host(source, (Host *)destination);
            result = PACKET_REACHED_DESTINATION;
        }
        else{
            /*Rotuer to Rotuer*/
            result = send_from_to_router(source, (Router *)destination);
        }
    }
    return result;
}

int action_host(Host *source, List *all_hosts){
    int dest_nr = rand() % all_hosts->length;
    int i;
    Item *destination = all_hosts->first;
    for(i = 0; i < dest_nr; i++){
        destination = destination->next;
    } 
    create_packet(*source, *(Host *)(destination->item), source->Send, 68);
    return  send_to_router(source, source->address->connection);
}

int loop_opjects(Btree *network, List *all_hosts, int tick){
    int rtn = 0; /*Packets lost*/
    if(network != NULL){
        /*Router*/
        if(*(int *) network->item == ROUTER){
            Router *active = (Router *)network->item;
            if(tick % active->speed == 0){
                rtn = (action_router(active) == 0);
            }
        }
        /*Host*/
        else{
            Host *active = (Host *)network->item;
            if(tick % active->speed == 0){
                rtn = (action_host(active, all_hosts) == 0);
            }
        }
        /*Do subtrees*/
        rtn += loop_opjects(network->greater, all_hosts, tick);
        rtn += loop_opjects(network->smaller, all_hosts, tick);
    }
    return rtn;
}
/*
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
