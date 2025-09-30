#ifndef BINARY_TREES_H
#define BINARY_TREES_H

#include <stddef.h>

/* Provided structure */
struct binary_tree_s
{
    int n;
    struct binary_tree_s *parent;
    struct binary_tree_s *left;
    struct binary_tree_s *right;
};

typedef struct binary_tree_s binary_tree_t;
typedef struct binary_tree_s avl_t;

/* Function prototypes */
binary_tree_t *binary_tree_node(binary_tree_t *parent, int value);
int binary_tree_is_avl(const binary_tree_t *tree);
void binary_tree_print(const binary_tree_t *);

#endif
