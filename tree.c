#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "router.h"
#include "malloc_check.h"

Btree btree_create(){
    Btree new;
    new.greater = NULL;
    new.smaller = NULL;
    new.item = NULL;
    return new;
}

void btree_add(Btree *tree, void * item, int (*compare)(const void *, const void *)){ 
    if(tree->item == NULL){
        tree->item = item;
    }
    else{
        Btree **active;
        if(compare(tree->item, item) > 0){
            active = &(tree->greater);
        }
        else{
            active = &(tree->smaller);
        }

        if(*active == NULL){
            Btree *new = (Btree *) malloc_check (sizeof(Btree)); 
            *new = btree_create();
            new->item = item;
            *active = new;
        }
        else{
            btree_add(*active, item, compare);
        }
    }
}

void *btree_find(Btree *tree, void * item, int (*compare)(const void *, const void *)){
    if (tree == NULL){ /*The item is not there*/
        return (void *)tree;
    }
    else{
        int result = compare(tree->item, item);
        if (result > 0){
            return btree_find(tree->greater, item, compare);
        }
        else if (result < 0){
            return btree_find(tree->smaller, item, compare);
        }
        else{
            return tree->item;
        }
    }
}
