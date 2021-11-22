#include "host.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

packet create_packet(){
    packet hi;
    hi.id = 4;
    return hi;
}

void host_create_package(host *source){ /*Hai*/
    /*Create a packet and place it in packet_creation*/
}

void host_receave_package(host *source){ /*Peter*/
    packet *check = (packet *) source->packet_receaving;
    if(check->id == source->id){
        printf("%s: I've got a packet.\n", source->name);
    }
    else{
        printf("%s: I haven't got a packet.\n", source->name);
    }
}

void host_send_package(host *source){ /*Hai*/
    /*Sends a packet from packet_creation to the connected router*/
}

host *host_create(int id, char name[HOST_NAME_SIZE], int speed){ /*Peter*/
    host *new = (host *)malloc(sizeof(host));

    if(new == NULL){
        printf("Couldn't allocate space for host %s\n", name);
        exit(EXIT_FAILURE);
    }

    new->id = id;
    strcpy(new->name, name);
    new->speed = speed;


    return new;
}

void host_connect(host *source, router *destination){ /*Peter*/
    source->connection = destination;
}

