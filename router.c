#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "router.h"
#include "host.h"

/*Prototype*/
void connect_router(Router r1, Router r2);
void connect_host(Router r, Host h);


/*Functions*/
void connect_router(Router r1, Router r2){
    Router r_one;
    Router r_two;
    int n;

    r_one.connections = (Router*) malloc(n * sizeof(Router)); //ikke færdigt.. det skal returnere det nuværende array for routeren der arbejdes med.
    r_two.connections = (Router*) malloc(n * sizeof(Router)); //ikke færdigt.. det skal returnere det nuværende array for routeren der arbejdes med. 

    Router *r_one_p;
    r_one_p = &r_one;
    
    Router *r_two_p;
    r_two_p = &r_two;

    r_one.connections[0] = *r_two_p;
    r_two.connections[0] = *r_one_p;
}

void connect_host(Router r, Host h){
    int n;

    r.connections = (Host*) malloc(n * sizeof(Host)); //ikke færdigt.. det skal returnere det nuværende array for routeren der arbejdes med.
    h.address = (Router*) malloc(n * sizeof(Router)); //ikke færdigt.. det skal returnere det nuværende array for routeren der arbejdes med. 

    Router *rp;
    rp = &r;
    
    Host *hp;
    hp = &h;

    r.connections[0] = *hp;
    h.address[0] = *rp;
}

int routingtree_insert(){
    return 0;
}

int routingtree_create(int n){
    int tree[n][n];
    for(int i = 0; i <= n; i++){
        for(int j = 0; j <= n; j++){
            tree[i][j] = 0;
        }
    }
    return tree;
}