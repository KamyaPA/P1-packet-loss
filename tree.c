#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

void btree_add(Btree *tree, void * item, int (*compare)(const void *, const void *)){
    Btree *new = (Btree *) malloc (sizeof(Btree));
    new->item = item;
    
    Btree *active;
    if(compare(active->item, item) > 1){
        active = tree->greater;
    }
    else{
        active = tree->smaller;
    }

    if(active == NULL){
        active = new;
    }
    else{
        btree_add(active, item, compare);
    }
}

void *btree_find(Btree *tree, void * item, int (*compare)(const void *, const void *)){
    int result = compare(tree->item, item);
    if (result > 0){
        return btree_find(tree->greater, item, compare);
    }
    else if (result < 0){
        return btree_find(tree->smaller, item,compare);
    }
    else{
        return tree->item;
    }
}
