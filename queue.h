#define INCLUDED_LIST_H
#define INCLUDED_QUEUE_H

typedef struct Item{
    struct Item *next;
    void *item;
} Item;

typedef struct Queue{
    int length;
    List *list;
} Queue;