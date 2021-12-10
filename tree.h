typedef struct Btree{
    struct Btree* greater;
    struct Btree* smaller;
    void *item;
}Btree;

void btree_add(Btree *tree, void * item, int (*compare)(const void *, const void *)); 
void *btree_find(Btree *tree, void * item, int (*compare)(const void *, const void *));
