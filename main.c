#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "host.h"

int main(int argc, char *argv[]){
    host *test = host_create(5, "Hello World", 1000);
    printf(
        "id = %d\n"
        "name = %s\n"
        "speed = %d\n"
        , test->id, test->name, test->speed
    );

    *((packet *)(test->packet_receaving)) = create_packet();
    host_receave_package(test);
    free(test);
    return 0;
}
