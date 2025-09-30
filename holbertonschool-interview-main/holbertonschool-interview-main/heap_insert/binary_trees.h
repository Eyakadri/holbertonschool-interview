#ifndef _BINARY_TREES_H_
#define _BINARY_TREES_H_

#include <stddef.h>

/**
 * struct binary_tree_s - Binary tree node
 *
 * @n: Integer stored in the node
 * @parent: Pointer to the parent node
 * @left: Pointer to the left child node
 * @right: Pointer to the right child node
 */
typedef struct binary_tree_s
{
	int n;
	struct binary_tree_s *parent;
	struct binary_tree_s *left;
	struct binary_tree_s *right;
} binary_tree_t;

typedef struct binary_tree_s heap_t; /* Alias for Max Binary Heap */

void binary_tree_print(const binary_tree_t *);
binary_tree_t *binary_tree_node(binary_tree_t *parent, int value);
heap_t *heap_insert(heap_t **root, int value);

/* Helper function prototypes */
size_t binary_tree_size(const binary_tree_t *tree);
heap_t *get_parent_node(heap_t *root, size_t index);
size_t binary_tree_find_index(size_t size);
void swap_values(heap_t *a, heap_t *b);

#endif /* _BINARY_TREES_H_ */
