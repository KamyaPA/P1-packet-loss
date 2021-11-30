#include <stdio.h>
#include <string.h>

#define ARGUMENTS 4 /*The max amount of arguments needed*/

void create_network(char *conf_file_path){
    char str[50];
    char delim[] = " ";
    char *command;
    char *arguments[ARGUMENTS];
    int line_nr = 1;

    strcpy(str, conf_file_path);
    command = strtok(str, delim);
    if(command[0] != '#'){
        int i = 0;
        char *argument;

        back:
        argument = strtok(NULL, delim);
        if(argument != NULL){
            arguments[i] = argument;
            i++;
            goto back;
        }

        if(strcmp(command, "addr") == 0){
            int capacity, speed;
            sscanf(arguments[1],"%d", &capacity);
            sscanf(arguments[2],"%d", &speed);
            printf("ADD: router, name %s, capacity %d, speed %d\n",
                   arguments[0], capacity, speed);
        }
        else if(strcmp(command, "addh") == 0){
            int speed;
            sscanf(arguments[1],"%d", &speed);
            printf("ADD: host, name %s, speed %d\n",
                   arguments[0], speed);
        }
        else if(strcmp(command, "conr") == 0){
            int length;
            sscanf(arguments[2],"%d", &length);
            printf("CONNECT: router name %s, router name %s, length %d\n",
                   arguments[0], arguments[1], length);
        }
        else if(strcmp(command, "conh") == 0){
            int length;
            sscanf(arguments[2],"%d", &length);
            printf("CONNECT: host name %s, router name %s, length %d\n",
                   arguments[0], arguments[1], length);
        }
    }
    line_nr++;
}

