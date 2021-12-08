typedef struct PacketHeader{
    unsigned int payload_length; /*How many bytes*/
    char hop_limit;
    host *source_address;
    host *destination_address;
} PacketHeader;