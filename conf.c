#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "create_function.h"
#include "tree.h"

#define ARGUMENTS 4         /*  The max amount of arguments needed.     */
#define ADDR_ARGUMENTS 3
#define ADDH_ARGUMENTS 2
#define CONR_ARGUMENTS 3
#define CONH_ARGUMENTS 3
#define MAX_STR_LN 50       /*  Max length of string.                   */

void wrong_command(char *command, int line_nr);
void arguments_check(int check, int target, int line_nr);
void router_add(Btree *network, Router *new);
void host_add(Btree *network, Host *new);
int name_compare(const void *, const void *);

void create_network(Btree *network, char *conf_file_path){
    FILE *file;
    char str[MAX_STR_LN];
    char delim[] = " \n";
    char *command;
    char *arguments[ARGUMENTS];
    int line_nr = 1;
 
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
                }
                else if(strcmp(command, "conr") == 0){ /*Connect router to router*/
                    int length;
                    arguments_check(i, CONR_ARGUMENTS, line_nr);
                    sscanf(arguments[2],"%d", &length);
                    printf("CONNECT: router name %s, router name %s, length %d\n",
                        arguments[0], arguments[1], length);
                }
                else if(strcmp(command, "conh") == 0){ /*Connect host to router*/
                    int length;
                    arguments_check(i, CONH_ARGUMENTS, line_nr);
                    sscanf(arguments[2],"%d", &length);
                    printf("CONNECT: host name %s, router name %s, length %d\n",
                        arguments[0], arguments[1], length);
                }
                else{                                  /*Error*/
                    wrong_command(command, line_nr);
                }
            }
        }
        line_nr++; /*Next line*/
    }
    fclose(file);   /*Closes open file */
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
