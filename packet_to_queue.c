#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "router.h"
#include "host.h"
#include "packet.h"
PacketHeader create_packet(Host H1, Host H2);
Router router_create(unsigned int speed_of_router, char *name_of_router, int length_of_queue, char *start_point, char *read_data, char *write_data);
Host host_create(unsigned int speed_of_host, char *name_of_host, char *send, char *receive, Router R);
void put_in_queue(Router R, PacketHeader P, int if_first);
char get_from_queue(Router R, int if_first);


int main(void){
Host h;
Host h2;
Router r;

h = host_create(1, "Host 1", r);
h2 = host_create(1, "Host 2", r);
r = router_create(1, "Router 1", 300);

put_in_queue(r, create_packet(h,h2), 1);
printf("%d", get_from_queue(r, 1));

}


PacketHeader create_packet(Host H1, Host H2){

   PacketHeader P;

   P.hop_limit = 255; // number can be changed
   P.source_address = H1.address;
   P.destination_address = H2.address;
   P.payload_length = sizeof(P.hop_limit) + sizeof(P.source_address) + sizeof(P.destination_address);

   return(P);
}

Router router_create(unsigned int speed_of_router, char *name_of_router, int length_of_queue){

Router R;
R.name = *name_of_router;
R.id = &R;
R.speed = speed_of_router;
//R.tree = 
R.queue.length = length_of_queue;
R.queue.start;
R.queue.read;
R.queue.write;

return(R);
}

// Speed, name, send, receive and router variabel of router struct will be input parameters

Host host_create(unsigned int speed_of_host, char *name_of_host, Router R){

Host H;
H.name = *name_of_host;
H.id = &H;
H.speed = speed_of_host;
H.address->id = &R;

return(H);
}

void put_in_queue(Router R, PacketHeader P, int if_first){

   char *queue;
   R.queue.start = *queue;
   char *pack_size = &P;

   queue = malloc((R.queue.length)*sizeof(char));
   if(if_first == 1){ // if_first used to determine if packet is the first received in queue and whether write pointer has to be at beginning
      R.queue.write = *queue;
      for(int i = 0; i < ((P).payload_length); i++){
      *(queue+i) = *(pack_size+i);
      R.queue.write + i;
   }
   }else{
      for(int i = 0; i < ((P).payload_length); i++){
      *(queue+i) = *(pack_size+i);
      R.queue.write + i;
      }
   }
   free(queue);
}

char get_from_queue(Router R, int if_first){

   PacketHeader P;
   char *queue;
   R.queue.start = *queue;
   char *read = R.queue.read;
   char *pack_size = &P;

   if(if_first == 1){
      R.queue.read = *queue;
      int payload =((PacketHeader*)read)->payload_length;
      queue = malloc((payload)*sizeof(char));
      for(int i = 0; i < payload; i++){
         *(queue+i) = *(pack_size+i);
         R.queue.read +i;
      }
   }else{
      int payload =((PacketHeader*)read)->payload_length;
      queue = malloc((payload)*sizeof(char));
      for(int i = 0; i < payload; i++){
         *(queue+i) = *(pack_size+i);
         R.queue.read +i;
      }
   }
   free(queue);
return pack_size;
}
