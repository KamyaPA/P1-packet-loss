#ifndef INCLUDED_ROUTER_H
    #include "router.h"
#endif
#ifndef INCLUDED_HOST_H
    #include "host.h"
#endif
#ifndef INCLUDED_PACKET_H
    #include "packet.h"
#endif

int send(Router *from, Router *to);
PacketHeader create_packet(Host H1, Host H2, void* where, int size_of_packet);
int send_to_router(Host *from, Router *to);
int send_to_host(Router *from, Host *to);
