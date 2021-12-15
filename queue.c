#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "queue.h"

Queue create_queue(){
    Queue new;
    new.list = NULL;
    new.length = 0;
    return new;
}

void queue_add(Queue *queue, void *item){
    Item *new = (Item *) malloc(sizeof(Item));
    new->item = item;
    if(queue->list->item == 0){
        queue->list->first = new;
    }
    else{
        Item *active = queue->list->first;
        while(active->next != NULL){
            active = active->next;
        }
        active->next = new;
    }
    queue->length++;
}

*Item queue_remove(Queue *queue, void *item){
    if(queue->list->first == NULL){
        char str[] = "Tried to remove an element from an empty queue";
        printf("%s", str);
    }
    else{
        Item *active = queue->list->first->next;
        Item *removed = queue->list->first;
        queue->list->first = active;
        return removed;
    }
}