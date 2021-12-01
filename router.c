#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <router.h>
#include <Hosts.h>

/*Prototype*/
void connect_router(Router r1, Router r2);
void connect_host(Router r, Host h);


/*Functions*/
void connect_router(Router r1, Router r2){
    struct Router r_one;
    struct Router r_two;

    int r_one.*connections = (int*) malloc(0 * sizeof(int)); //ikke færdigt.. det skal returnere det nuværende array for routeren der arbejdes med.
    int r_two.*connections = (int*) malloc(0 * sizeof(int)); //ikke færdigt.. det skal returnere det nuværende array for routeren der arbejdes med. 

    struct Router *r_one_p;
    r_one_p = &r_one;
    
    struct Router *r_two_p;
    r_two_p = &r_two;
}

void connect_host(Router r, Host h){
    struct Router r;
    struct Host h;

    int r_one.*connections = (int*) malloc(0 * sizeof(int)); //ikke færdigt.. det skal returnere det nuværende array for routeren der arbejdes med.
    int r_two.*connections = (int*) malloc(0 * sizeof(int)); //ikke færdigt.. det skal returnere det nuværende array for routeren der arbejdes med. 

    struct Router *r_one_p;
    r_one_p = &r_one;
    
    struct Router *r_two_p;
    r_two_p = &r_two;
}

int routingtree_insert(){


}

int routingtree_create(){
    int n; /*number of routers in the network*/
    int tree[n][n];
    for(int i = 0, i <= n, i++){
        for(int j = 0, j <= n, j++){
            tree[i][j] = 0;
        }
    }
    return tree[][];
}
