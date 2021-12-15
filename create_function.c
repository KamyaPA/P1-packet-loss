#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "router.h"
#include "host.h"

// Speed, name and capacity(length of queue) will be input parameters along with a router struct

Router router_create(unsigned int speed_of_router, char *name_of_router, int length_of_queue, char *start_point, char *read_data, char *write_data){

Router R;
R.name = *name_of_router;
R.id = &R;
R.speed = speed_of_router;
//R.tree = 
R.queue.length = length_of_queue;
R.queue.start = *start_point;
R.queue.read = *read_data;
R.queue.write = *write_data;

return(R);
}

// Speed, name, send, receive and router variabel of router struct will be input parameters

Host host_create(unsigned int speed_of_host, char *name_of_host, char *send, char *receive, Router R){

Host H;
H.name = *name_of_host;
H.id = &H;
H.speed = speed_of_host;
H.Send = *send;
H.Receive = *receive;
H.address->id = &R;

return(H);
}


