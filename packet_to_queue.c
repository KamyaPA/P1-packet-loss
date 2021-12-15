#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "router.h"
#include "host.h"
#include "packet.h"
#include "create_function.h"
PacketHeader create_packet(Host H1, Host H2);
Router router_create(unsigned int speed_of_router, char *name_of_router, int length_of_queue, char *start_point, char *read_data, char *write_data);
Host host_create(unsigned int speed_of_host, char *name_of_host, char *send, char *receive, Router R);
void put_in_queue(Router R, PacketHeader P, int if_first);
char get_from_queue(Router R, int if_first);


int main(void){
Host h;
Host h2;
Router r;

h = host_create(1, "Host 1");
h2 = host_create(1, "Host 2");
r = router_create(1, "Router 1", 300);


}


PacketHeader create_packet(Host H1, Host H2, void* where, int size_of_packet){

   PacketHeader P;

   P.hop_limit = 255; // number can be changed
   P.source_address = H1.address;
   P.destination_address = H2.address;
   P.payload_length = (size_of_packet) - sizeof(PacketHeader);

   return(P);
}

Router router_create(unsigned int speed_of_router, char *name_of_router, int length_of_queue){
    Router R;
    R.type = ROUTER;
    R.name = (char *) malloc (strlen(name_of_router));
    strcpy(R.name, name_of_router);
    R.id = &R;
    R.speed = speed_of_router;
    /*R.tree =*/ 
    R.queue.length = length_of_queue;
    R.queue.start = (char *) malloc (length_of_queue);
    R.queue.read = R.queue.start;
    R.queue.write = R.queue.start;

    return(R);
}

// Speed, name, send, receive and router variabel of router struct will be input parameters

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

void put_in_queue(Router R, PacketHeader *P){

   char *pack_size = P;

   for(int i = 0; i < ((P)->payload_length); i++){
      *(R.queue.write++) = *(pack_size+i);
      if((R.queue.write - R.queue.start) > R.queue.length) 
         R.queue.write = R.queue.start;
   }  
}

char get_from_queue(Router R){

   PacketHeader P;
   char *pack_size = (char*)&P;

   for(int i = 0; i < P.payload_length; i++){
      *(R.queue.read++) = *(pack_size+i);
      R.queue.read +i;
   }
   
return pack_size;
}

int send(Router *from, Router *to){
   char * PH = malloc(sizeof(PacketHeader));
   char * Packet;
   for(int i =0; i < sizeof(PacketHeader); i++){

      *(PH+i) = *(from->queue.read++);
      if(from->queue.read - from->queue.start > from->queue.length){
         from->queue.read = from->queue.start;
      }
   }
   (PacketHeader*)PH;
   int length = ((PacketHeader *)PH)->payload_length;
   Packet = malloc(sizeof(length));
   for(int i =0; i < length; i++){
      *(Packet+i) = *(from->queue.read++);
      if(from->queue.read - from->queue.start > from->queue.length){
         from->queue.read = from->queue.start;
      }
   }
   if(length + sizeof(PacketHeader) < space_left(to)){
      for(int i =0; i < sizeof(PacketHeader); i++){

         *(to->queue.write++)= *(PH+i);
         if(to->queue.write - to->queue.start > to->queue.length){
            to->queue.write = to->queue.start;
         }
      }
      for(int i =0; i < length; i++){
         *(to->queue.write++) = *(Packet+i);
         if(to->queue.write - to->queue.start > to->queue.length){
            to->queue.write = to->queue.start;
         }
      }
      return_val = 1;
   }
   else{
      return_val = 0;      
   }
   free(PH);
   free(Packet);
   return return_val;
}
int space_left(Router *R){
   if(R->queue.read > R->queue.write){
      return R->queue.read - R->queue.write;
   }
   else if(R->queue.read < R->queue.write){
      return R->queue.length - (R->queue.write - R->queue.read)
   }
   else{
      return R->queue.length;
   }
}