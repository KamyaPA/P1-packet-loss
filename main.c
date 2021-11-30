#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "conf.h"

int main(int argc, char *argv[]){
    create_network("addr foo    255 8 ");
    create_network("addr hi 128 9");
    create_network("addh bar      6");

    create_network("conh bar foo 7");
    create_network("conr foo hi 4");
    create_network("#conr router2 router3 4");
    return 0;
}
