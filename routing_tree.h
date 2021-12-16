#define INCLUDED_ROUTINGTREE_H

typedef struct RtreeItem{
    void *node;
    struct RtreeItem *node_before;
} RtreeItem;


int list_tree(char *read_file, char *write_file);
