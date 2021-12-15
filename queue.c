#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "queue.h"

/*Queue is a first in first out. Adding an item puts it in the back of the queue, removing an item takes the first element out.*/
Queue create_queue(){
    Queue new;
    new.list = NULL;
    new.length = 0;
    return new;
}

/*Puts an item in the back of the queue*/
void queue_add(Queue *queue, void *item){
    //Allocates memory to the item in the queue
    Item *new = (Item *) malloc(sizeof(Item));
    new->item = item;

    //If the queue is empty, the item is placed as the first(and only) element in the queue. Else, place at the back of the queue.
    if(queue->list->first == 0){
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

/*Removes the first item in the queue and returns a void pointer to it.*/
void* queue_remove(Queue *queue, void *item){
    //Checks is the queue is empty. If its empty, it will write so in the terminal
    if(queue->list->first == NULL){
        char str[] = "Tried to remove an element from an empty queue";
        printf("%s", str);
    }
    //Removes and returns the first item
    else{
        //makes pointers to the first and second element in the list. 
        Item *active = queue->list->first->next;
        Item *removed = queue->list->first;

        //makes the 2nd element in the list the new first element
        queue->list->first = active;

        //dereferences the item from the queue and frees the memory allocated to store the temporary item
        void* removed_item = removed->item;
        free(removed);
        return removed_item;
    }
}