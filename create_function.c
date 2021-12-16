#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "router.h"
#include "host.h"
#include "packet.h"
#include "create_function.h"
#ifndef INCLUDED_LIST_H
    #include "list.h"
#endif

/* Speed, name and capacity(length of queue) will be input parameters along with a router struct*/

Router router_create(unsigned int speed_of_router, char *name_of_router, int length_of_queue){
    Router R;
    R.type = ROUTER;
    R.name = (char *) malloc (strlen(name_of_router));
    strcpy(R.name, name_of_router);
    R.id = &R;
    R.speed = speed_of_router;
    R.routing_tree = NULL; 
    R.queue.length = length_of_queue;
    R.queue.start = (char *) malloc (length_of_queue);
    R.queue.read = R.queue.start;
    R.queue.write = R.queue.start;

    R.connections = create_list();

    return(R);
}

/* Speed, name, send, receive and router variabel of router struct will be input parameters*/

Host host_create(unsigned int speed_of_host, char *name_of_host){
    Host H;
    H.type = HOST;
    H.name = (char *) malloc (strlen(name_of_host));
    strcpy(H.name, name_of_host);
    H.id = &H;
    H.speed = speed_of_host;
    H.Send = (char *) malloc (sizeof(PacketHeader) + 255);
    H.Receive = (char *) malloc (sizeof(PacketHeader) + 255);
    return(H);
}
