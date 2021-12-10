#define INCLUDED_LIST_H

typedef struct Item{
    struct Item *next;
    void *item;
} Item;

typedef struct List{
    int length;
    Item *first;
} List;

List create_list();
void list_add(List *list, void *item);
