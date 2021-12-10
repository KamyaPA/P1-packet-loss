#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "hostOrRouter.h"
#include "router.h"
#include "host.h"
#include "packet.h"

typedef struct packet{
    int length;
    int id; //(1,2,3...)
} Packet;

// Creating packet
void create_packet(Packet *m)
{
    int i, n;
    printf(" How many packet?: ");
    scanf("%d", &n);
    m = (Packet*)malloc(n*sizeof(Packet));
    for(i=0; i<n; i++)
    {
        printf(" Packets length (bytes): ");
        scanf("%d", m->length);
        m->id = i++;
    }
}

// creating packets header
void create_packet_header(Packet *m, Host *source, Host *destination)
{
    PacketHeader *mh 
    mh = (PacketHeader*)malloc(sizeof(PacketHeader));
    if(m==NULL)
    {   printf(" Coundn't provide memory");
        exit(0);
    }
    *(mh->hop_limit)=255;
    *(mh->source_address) = *(source->id);
    *(mh->destination_address) = *(destination->id);
    *(mh->payload_length) = sizeof *(m->length) + sizeof *(mh->hop_limit) +
                            sizeof *(mh->source_address) + sizeof *(mh->destination_address);
}

// Checking packetheader
int check_PacketHeader(PacketHeader *mh, host *source, host *destination)
{
    int check;
    if(*(mh->source_address)==*(source->id)&&
       *(mh->destination_address) = *(destination->id))
    {
        check = 1;
        (*(mh->hop_limit))--;
    }
    else
    {
        check = 0;
       (*(mh->hop_limit))--;
    }
    return check;
}

// Sending packet
void host_send_packet(PacketHeader *mh, Host *source, Host *destination, RoutingTree *list)
{
    int count, check, packet_lost;
    check = check_PacketHeader(&mh, &source, &destination);
    if(check==1) // router receive packet
    {
        for(i=0; i<(sizeof list; i++) // list: routers give a short way.
        {
            if(*(host->speed>0) && *(mh->hop_limit)!=0 ) // relative speed: 0-1 (0: congestion, 1: maximum speed)
            {    
                count++; // send packet
                (*(mh->hop_limit))--;
            }
            else
            {
                count = 0;
                packet_lost = *list[i];
                (*(mh->hop_limit))--;
            }
        }
    }
    else
    {
        printf(" The packet is lost");
        (*(mh->hop_limit))--;
    }
    if(count==(sizeof list) && *(mh->hop_limit)!=0)
        printf(" The packet is sent successfully");
    else
        printf(" The packet lost at router %d", packet_lost);
}


