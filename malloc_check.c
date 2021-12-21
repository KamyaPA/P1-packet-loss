#include <stdlib.h>
#include <stdio.h>

void *malloc_check(int size){
    void *new =  malloc(size);
    if(new == NULL){
        printf("Couln'd allocate the space needed\n");
        exit(1);
    }
    return new;
}
