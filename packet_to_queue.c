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
int send(Router *from, Router *to);
int space_left(Router *R);



PacketHeader create_packet(Host H1, Host H2, void* where, int size_of_packet){

   PacketHeader P;

   P.hop_limit = 255; // number can be changed
   P.source_address = H1.address;
   P.destination_address = H2.address;
   P.payload_length = (size_of_packet) - sizeof(PacketHeader);

   return(P);
}


int send(Router *from, Router *to){
   int return_val;
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
      return R->queue.length - (R->queue.write - R->queue.read);
   }
   else{
      return R->queue.length;
   }
}