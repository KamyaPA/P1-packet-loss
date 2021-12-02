#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARGUMENTS 4         /*  The max amount of arguments needed.     */
#define ADDR_ARGUMENTS 3
#define ADDH_ARGUMENTS 2
#define CONR_ARGUMENTS 3
#define CONH_ARGUMENTS 3
#define MAX_STR_LN 50       /*  Max length of string.                   */

void wrong_command(char *command, int line_nr);
void to_few_arguments_check(int check, int target, int line_nr);

void create_network(char *conf_file_path){
    FILE *file;
    char str[MAX_STR_LN];
    char delim[] = " \n";
    char *command;
    char *arguments[ARGUMENTS];
    int line_nr = 1;

    file = fopen(conf_file_path, "r");  /*  Opens specific file.                    */

    while (fgets(str, MAX_STR_LN, file)){   /*  Reads a file, line by line.   */
        command = strtok(str, delim);
        if(command[0] != '#'){
            int i = 0;
            char *argument;

            while(argument = strtok(NULL, delim)){
                arguments[i] = argument;
                i++;
            }

            if(strcmp(command, "addr") == 0){
                int capacity, speed;
                to_few_arguments_check(i, ADDR_ARGUMENTS, line_nr);
                sscanf(arguments[1],"%d", &capacity);
                sscanf(arguments[2],"%d", &speed);
                printf("ADD: router, name %s, capacity %d, speed %d\n",
                    arguments[0], capacity, speed);
            }
            else if(strcmp(command, "addh") == 0){
                int speed;
                to_few_arguments_check(i, ADDH_ARGUMENTS, line_nr);
                sscanf(arguments[1],"%d", &speed);
                printf("ADD: host, name %s, speed %d\n",
                    arguments[0], speed);
            }
            else if(strcmp(command, "conr") == 0){
                int length;
                to_few_arguments_check(i, CONR_ARGUMENTS, line_nr);
                sscanf(arguments[2],"%d", &length);
                printf("CONNECT: router name %s, router name %s, length %d\n",
                    arguments[0], arguments[1], length);
            }
            else if(strcmp(command, "conh") == 0){
                int length;
                to_few_arguments_check(i, CONH_ARGUMENTS, line_nr);
                sscanf(arguments[2],"%d", &length);
                printf("CONNECT: host name %s, router name %s, length %d\n",
                    arguments[0], arguments[1], length);
            }
            else{
                wrong_command(command, line_nr);
            }
        }
        line_nr++;
    }
    fclose(file);   /*  Closes open file.   */
}

void to_few_arguments_check(int check, int target, int line_nr){
    if(check != target){
        printf("To few arguments on line %d, expected %d and got %d\n",
               line_nr, target, check);
        exit(EXIT_FAILURE);
    }
}

void wrong_command(char *command, int line_nr){
    printf("Wrong command syntax on line %d, got %s\n",
            line_nr, command);
    exit(EXIT_FAILURE);
}
