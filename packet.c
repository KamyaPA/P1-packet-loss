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
