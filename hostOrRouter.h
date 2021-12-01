#include "host.h"
#include "router.h"
struct host_or_router{
    int type;
    struct host_or_router *p;
}; host_or_router;

union hostorrouter{
    Host *p_host;
    Router *p_router;
};