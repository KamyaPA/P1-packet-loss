#include <stdio.h>
#include <string.h>

int main(){
    char str[] = "       #addr router1    255 8";
    char delim[] = " ";
    char *substr;
    substr = strtok(str, delim);
    if(substr[0] != '#'){
        if (strcmp(substr, "addr") == 0){
            int speed, capacity;
            char *name;
            name = strtok(NULL, delim);
            sscanf(strtok(NULL, delim), "%d", &capacity);
            sscanf(strtok(NULL, delim), "%d", &speed);
            printf("Name = %s, capacity = %d, speed = %d\n", name, capacity, speed);
        }
        else if (strcmp(substr, "addh")){
            /*Add host*/
        }
    }
/*
    do{
        printf("%s\n", substr);
        substr = strtok(NULL, delim);
    }while(substr != NULL);
    */
    return 0;
}

