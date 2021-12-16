#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "create_function.h"
#include "tree.h"

#ifndef INCLUDED_ROUTINGTREE_H
#include "routing_tree.h"
#endif

#ifndef INCLUDED_ROUTER_H
#include "router.h"
#endif

#define ARGUMENTS 4         /*  The max amount of arguments needed.     */
#define ADDR_ARGUMENTS 3
#define ADDH_ARGUMENTS 2
#define CONR_ARGUMENTS 3
#define CONH_ARGUMENTS 3
#define MAX_STR_LN 50       /*  Max length of string.                   */

#define ROUTING_TREE_IN_FILNAME "dijkstras_in.tmp"
#define ROUTING_TREE_OUT_FILNAME "dijkstras_out.tmp"


void wrong_command(char *command, int line_nr);
void not_defined(char *object, int line_nr);
void arguments_check(int check, int target, int line_nr);
void router_add(Btree *network, Router *new);
void host_add(Btree *network, Host *new);
int name_compare(const void *, const void *);
int find_compare(const void * tree, const void * item);
int copy_tree(Btree *tree, void **arr, int copied_objects);
int pointer_compare(const void *p1, const void * p2);
int linier_search(void **arr, void *what, int length);

void create_network(Btree *network, char *conf_file_path){
    FILE *file;
    char str[MAX_STR_LN];
    char delim[] = " \n";                   /*Delimiters in strtok*/
    char *command;
    char *arguments[ARGUMENTS];
    int line_nr = 1;

    int network_nodes = 0;                  /*For setting up the routingtree function*/
    int network_edges = 0;
 
    file = fopen(conf_file_path, "r");      /*  Opens specific file.          */

    while (fgets(str, MAX_STR_LN, file)){   /*  Reads a file, line by line.   */
        if(strcmp(str, "\n") != 0){         /*  Is it an empty line           */
            command = strtok(str, delim);
            if(command[0] != '#'){          /*  Is it a commed                */
                int i = 0;
                char *argument;
                while((argument = strtok(NULL, delim))){ /*Load arguments to array*/
                    arguments[i] = argument;
                    i++;
                }

                if(strcmp(command, "addr") == 0){   /*Add router*/
                    Router *new = (Router *) malloc (sizeof(Router));
                    int capacity, speed;
                    arguments_check(i, ADDR_ARGUMENTS, line_nr);
                    sscanf(arguments[1],"%d", &capacity);
                    sscanf(arguments[2],"%d", &speed);
                    printf("ADD: router, name %s, speed %d, capacity %d\n",
                        arguments[0], speed, capacity);
                    *new = router_create(speed, arguments[0], capacity);
                    router_add(network, new);
                    network_nodes++;
                }
                else if(strcmp(command, "addh") == 0){ /*Add host*/
                    Host *new = (Host *) malloc (sizeof(Host));
                    int speed;
                    arguments_check(i, ADDH_ARGUMENTS, line_nr);
                    sscanf(arguments[1],"%d", &speed);
                    printf("ADD: host, name %s, speed %d\n",
                        arguments[0], speed);
                    *new = host_create(speed, arguments[0]);
                    host_add(network, new);
                    network_nodes++;
                }
                else if(strcmp(command, "conr") == 0){ /*Connect router to router*/
                    int length;
                    void *r1, *r2;
                    arguments_check(i, CONR_ARGUMENTS, line_nr);
                    sscanf(arguments[2],"%d", &length);
                    printf("CONNECT: router name %s, router name %s, length %d\n",
                        arguments[0], arguments[1], length);
                    
                    r1 = btree_find(network, arguments[0], find_compare);
                    if(r1 == NULL){
                        not_defined(arguments[0], line_nr);
                    }

                    r2 = btree_find(network, arguments[1], find_compare);
                    if(r2 == NULL){
                        not_defined(arguments[1], line_nr);
                    }

                    connect(r1, r2, length);
                    network_edges++;
                }    
                else if(strcmp(command, "conh") == 0){ /*Connect host to router*/
                    int length;
                    void *host, *router;
                    arguments_check(i, CONH_ARGUMENTS, line_nr);
                    sscanf(arguments[2],"%d", &length);
                    printf("CONNECT: host name %s, router name %s, length %d\n",
                        arguments[0], arguments[1], length);
                    
                    /*Error check*/
                    host = btree_find(network, arguments[0], find_compare);
                    if(host == NULL){
                        not_defined(arguments[0], line_nr);
                    }
                    
                    router = btree_find(network, arguments[1], find_compare);
                    if(router == NULL){
                        not_defined(arguments[1], line_nr);
                    }

                    connect(host, router, length);
                    network_edges++;
                }
                else{                                  /*Error*/
                    wrong_command(command, line_nr);
                }
            }
        }
        line_nr++; /*Next line*/
    }
    fclose(file);   /*Closes open file */
    
    {   /*Setting up dijstras*/

        /*Configfile for dijkstras*/
        FILE *routing_tree_file;
        int i;

        /*Declaration for searching*/
        Item *active;
        int found_index;
        
        /*Setup for routing tree*/
        void **all_nodes = (void **)malloc(sizeof(void *) * network_nodes);
        copy_tree(network, all_nodes, 0);

        /*Sort each network item by spot in memory*/
        /*qsort(all_nodes, network_nodes, sizeof(void *), pointer_compare);
        
        for(i = 0; i < network_nodes - 1; i++){
            printf("%d %d %p\n", all_nodes[i] > all_nodes[i + 1], all_nodes[i] == all_nodes[i + 1], all_nodes[i]);
        } 
        exit(-1);*/
        /*Creates the configfile for the dijstras algorithem*/
        routing_tree_file = fopen(ROUTING_TREE_IN_FILNAME, "w");

        fprintf(routing_tree_file, "%d %d\n", network_nodes, network_edges);
        for(i = 0; i < network_nodes - 1; i++){
            if(*(int *)all_nodes[i] == ROUTER){
                Router *object = (Router *)all_nodes[i];   
                for(active = object->connections.first; active != NULL; active = active->next){ /*Find connections*/
                    found_index = linier_search(all_nodes, ((Edge *)(active->item))->connection, network_nodes);
                    if(i < found_index){
                        fprintf(routing_tree_file,"%d %d %d\n", i + 1, found_index + 1, ((Edge *)(active->item))->length);
                    }
                }
            }
            else{
                Host *object = (Host *)(all_nodes[i]);
                found_index = linier_search(all_nodes, object->address->connection, network_nodes);
                if(i < found_index){
                    fprintf(routing_tree_file, "%d %d %d\n", i + 1, found_index + 1, object->address->length);
                }
            }   
        } 
        fclose(routing_tree_file);

        list_tree(ROUTING_TREE_IN_FILNAME, ROUTING_TREE_OUT_FILNAME);

        /*TRANSLATING OUTPUTFILE*/

        routing_tree_file = fopen(ROUTING_TREE_OUT_FILNAME, "r");
        while(!feof(routing_tree_file)){
            int router_index;
            int tree_index;
            int desination;
            int visited_before;
            
            fscanf(routing_tree_file, "%d", &router_index);
            router_index--; /*Beaceuse an array starts with a null, and the file starts at one*/
            if(*(int *)all_nodes[router_index] == ROUTER){
                Router *active_router = (Router *)all_nodes[router_index];
                desination = router_index; /* Important for a 1 distance network */

                if(active_router->routing_tree == NULL){ /*Allocate space for the routing tree*/
                    active_router->routing_tree = (RtreeItem *) malloc (network_nodes * sizeof(RtreeItem) - 1);
                    if(active_router->routing_tree == NULL){
                       printf("Couldn't allocate the space for malloc");
                      exit(1); 
                    }
                }

                if(fgetc(routing_tree_file) != '\n'){
                    visited_before = desination;
                    fscanf(routing_tree_file, "%d", &desination);
                    desination--; /*Beaceuse an array starts with a null, and the file starts at one*/
                    tree_index = router_index < desination ? router_index : router_index - 1;
                    
                    if(active_router->routing_tree[tree_index].node != NULL){
                        active_router->routing_tree[tree_index].node = all_nodes[desination];
                        active_router->routing_tree[tree_index].node_before = all_nodes[visited_before];
                    }
                }
            }         
        }
        free(all_nodes);
        fclose(routing_tree_file);
    }
}

void arguments_check(int check, int target, int line_nr){
    if(check != target){
        printf("To %s arguments on line %d, expected %d and got %d\n",
               check > target ? "many" : "few",line_nr, target, check);
        exit(EXIT_FAILURE);
    }
}

void wrong_command(char *command, int line_nr){
    printf("Wrong command syntax on line %d, got %s\n",
            line_nr, command);
    exit(EXIT_FAILURE);
}

void not_defined(char *object, int line_nr){
    printf("Objeckt \"%s\" not defined on line %d\n", object, line_nr);
    exit(EXIT_FAILURE); 
}

void router_add(Btree *network, Router *new){
    btree_add(network, (void *)new, name_compare);
}

void host_add(Btree *network, Host *new){
    btree_add(network, (void *)new, name_compare);
}

int name_compare(const void *item1, const void *item2){
    char *name1;
    char *name2;
    if(*((int *)item1) == ROUTER ){
        name1 = ((Router *)item1)->name;
    }
    else{
        name1 = ((Host *)item1)->name;
    }
    
    if(*((int *)item2) == ROUTER ){
        name2 = ((Router *)item2)->name;
    }
    else{
        name2 = ((Host *)item2)->name;
    }
    return strcmp(name1, name2);
}

int find_compare(const void * tree, const void * item){
    char *tree_name;
    tree_name = *(int *)tree == ROUTER ? ((Router *)tree)->name : ((Host *)tree)->name;
    return strcmp(tree_name, (char *)item);
}

/*Copies every item from a tree to an array*/
int copy_tree(Btree *tree, void **arr, int copied_objects){
    if(tree != NULL){ 
        arr[copied_objects] = tree->item;
        copied_objects++;
        copied_objects = copy_tree(tree->greater, arr, copied_objects);
        copied_objects = copy_tree(tree->smaller, arr, copied_objects);
    }
    return copied_objects;
}

int pointer_compare(const void *p1, const void * p2){
    return p1 > p2 ? 1 : -1;
}

int linier_search(void **arr, void *what, int length){
    int i;
    for(i = 0; i < length; i++){
        if(arr[i] == what){
            return i;
        }
    }
    return -1;
}
