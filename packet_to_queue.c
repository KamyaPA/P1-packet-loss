#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "router.h"
#include "host.h"
#include "packet.h"
#include "create_function.h"
int send(Router *from, Router *to);
int space_left(Router *R);



PacketHeader create_packet(Host H1, Host H2, void* where, int size_of_packet){
    PacketHeader P;
    int i;
    
    P.hop_limit = -1; // number can be changed
    P.source_address = H1.id;
    P.destination_address = H2.id;
    P.payload_length = (size_of_packet) - sizeof(PacketHeader);

    *((PacketHeader *)where) = P;
    for(i = 0; i < P.payload_length; i++){
        *(((char *)where) + sizeof(PacketHeader) + i) = '\0';
    }

    return(P);
}


int send(Router *from, Router *to){
    int return_val;
    PacketHeader PH;
    char * Packet;
    for(int i =0; i < sizeof(PacketHeader); i++){

        ((char *)&PH)[i] = *(from->queue.read++);
        if(from->queue.read - from->queue.start > from->queue.length){
            from->queue.read = from->queue.start;
        }
    }
    int length = PH.payload_length;
    Packet = (char *) malloc(sizeof(length));
    for(int i =0; i < length; i++){
        Packet[i] = *(from->queue.read++);
        if(from->queue.read - from->queue.start > from->queue.length){
            from->queue.read = from->queue.start;
        }
    }
    if(length + sizeof(PacketHeader) < space_left(to)){
        for(int i =0; i < sizeof(PacketHeader); i++){

            *(to->queue.write++) = ((char *)&PH)[i];
            if(to->queue.write - to->queue.start > to->queue.length){
                to->queue.write = to->queue.start;
            }
        }
        for(int i =0; i < length; i++){
            *(to->queue.write++) = Packet[i];
            if(to->queue.write - to->queue.start > to->queue.length){
                to->queue.write = to->queue.start;
            }
        }
        return_val = 1;
    }
    else{
        return_val = 0;      
    }
    free(Packet);
    return return_val;
}

int send_to_router(Host *from, Router *to){
    PacketHeader *header = (PacketHeader *)(from->Send);
    int length = sizeof(PacketHeader) + header->payload_length;
    int i;
    if(length < space_left(to)){
        for(i = 0; i < length; i++){
            *(to->queue.write++) = from->Send[i];
            if(to->queue.write - to->queue.start > to->queue.length){
                to->queue.write = to->queue.start;
            }
        }
        return 1;
    }
    else{
        return 0;
    }
}

int send_to_host(Router *from, Host *to){
    PacketHeader header;
    int i;
    /*Get the header*/
    for(i = 0; i < sizeof(PacketHeader); i++){
        ((char *)&header)[i] = *(from->queue.read++);
        if(from->queue.read - from->queue.start > from->queue.length){
            from->queue.read = from->queue.start;
        }
    }
    *((PacketHeader *)to->Receive) = header;
    /*Get the rest*/
    for(i = 0; i <  header.payload_length; i++){ 
        to->Send[i + sizeof(PacketHeader)] = *(from->queue.read++);
        if(from->queue.read - from->queue.start > from->queue.length){
            from->queue.read = from->queue.start;
        }
    }
    return 1;
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
