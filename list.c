#include <stdio.h>
#include <stdlib.h>
#include "list.h"

List create_list(){
    List new;
    new.first = NULL;
    new.length = 0;
    return new;
}

void list_add(List *list, void *item){
    Item *new = (Item *) malloc (sizeof(Item));
    new->item = item;
    new->next = NULL;
    if(list->length == 0){
        list->first = new;
    }
    else{
        Item *active = list->first;
        while(active->next != NULL){
            active = active->next;
        }
        active->next = new;
    }
    list->length++;
}


