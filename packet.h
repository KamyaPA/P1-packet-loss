#define INCLUDED_PACKET_H

#ifndef INCLUDED_HOST_H
#include "host.h"
#endif

typedef struct PacketHeader{
    unsigned int payload_length; /*How many bytes*/
    char hop_limit;
    Host *source_address;
    Host *destination_address;
} PacketHeader;
