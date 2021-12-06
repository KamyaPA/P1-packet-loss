typedef struct PacketHeader{
    unsigned int payload_length; /*How many bytes*/
    char hop_limit;
    Host *source_address;
    Host *destination_address;
} PacketHeader;