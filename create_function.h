#define INCLUDED_CREATE_FUNCTION_H
#ifndef INCLUDED_ROUTER_H
#include "router.h"
#endif
#ifndef INCLUDED_HOST_H
#include "host.h"
#endif

#define ROUTER 1
#define HOST 2

Host host_create( unsigned int speed_of_host, char *name_of_host);
Router router_create( unsigned int speed_of_router, char *name_of_router, int length_of_queue);
