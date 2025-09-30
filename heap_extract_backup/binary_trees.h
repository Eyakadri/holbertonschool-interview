#ifndef BINARY_TREES_H
#define BINARY_TREES_H

#include <stddef.h>
#include <stdlib.h>

/**
 * struct binary_tree_s - Binary tree node
 *
 * @n: Integer stored in the node
 * @parent: Pointer to the parent node
 * @left: Pointer to the left child node
 * @right: Pointer to the right child node
 */
struct binary_tree_s
{
	int n;
	struct binary_tree_s *parent;
	struct binary_tree_s *left;
	struct binary_tree_s *right;
};

typedef struct binary_tree_s binary_tree_t;
typedef struct binary_tree_s heap_t;


size_t binary_tree_height(heap_t *node);
void find_last_node(heap_t *node, size_t lvl, heap_t **last);
void replace_root(heap_t **root, heap_t **l, heap_t **r, heap_t **last);
void heapify_down(heap_t **root, heap_t *node, int *cont);

#endif  /* _BINARY_TREES_H_ */
