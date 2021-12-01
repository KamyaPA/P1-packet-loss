// creating packet and its header
Void host_create_packet(host *source, host *destination)
{
    PacketHeader *m 
    m = (PacketHeader*)malloc(sizeof(PacketHeader));
    if(m==NULL)
    {   printf(" Coundn't create packet");
        exit(0);
    }
    printf("Input length of packet (bytes): ");
    scanf("%d", &m->payload_length);
    *(m->source_address) = *(source->id);
    *(m->destination_address) = *(destination->id);
}

// Checking packetheader
int check_PacketHeader(PacketHeader *m, host *source, host *destination)
{
    int check;
    if(*(m->source_address)==*(source->id)&&
       *(m->destination_address) = *(destination->id))
       check = 1;
    else
       check = 0;
    return check;
}

// Sending packet
void host_send_packet(PacketHeader *m, host *source, host *destination, RoutingTree *list[])
{
    int count, check, packet_lost;
    check = check_PacketHeader(&m, &source, &destination);
    if(check==1)
        for(i=0; i<list; i++) 
        {
            if(*(host->speed>0)) // speed: 0-1
                count++; // send packet
            else
            {
                count = 0;
                packet_lost = *list[i];
            }
        }
    else
        printf(" The packet is not created or lost");
    
    if(count==list-1)
        printf(" The packet is sent successfully");
    else
        printf(" The packet lost at router %d", packet_lost);
}
