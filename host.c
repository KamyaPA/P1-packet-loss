#include "host.h"

packet create_packet(){
    packet hi;
    hi.id = 5;
    return hi;
}

void host_create_package(host *source){ /*Hai*/
    /*Create a packet and place it in packet_creation*/
}

void host_receave_package(host *source){ /*Peter*/
    /*Receave packet from connected router*/
}

void host_send_package(host *source){ /*Hai*/
    /*Sends a packet from packet_creation to the connected router*/
}

host *host_create(){ /*Peter*/
    /*Creates a new host*/
    host hi;
    return &hi;
}

void host_connect(host *source, router *destination){ /*Peter*/
    /*Establiches a connection between a router*/
}
