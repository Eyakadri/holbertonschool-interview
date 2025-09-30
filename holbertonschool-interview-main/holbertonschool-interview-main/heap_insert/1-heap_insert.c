#include <stdlib.h>
#include <stdio.h>
#include "binary_trees.h"

/**
 * heap_insert - Inserts a value into a Max Binary Heap.
 * @root: Double pointer to the root node of the Heap.
 * @value: The value to insert in the heap.
 *
 * Return: Pointer to the newly inserted node, or NULL on failure.
 */
heap_t *heap_insert(heap_t **root, int value)
{
	heap_t *new_node, *parent;
	size_t size, index;

	if (!root)
		return (NULL);

	if (*root == NULL)
	{
		*root = binary_tree_node(NULL, value);
		return (*root);
	}

	/* Find the correct position to insert */
	size = binary_tree_size(*root);
	index = binary_tree_find_index(size + 1);
	parent = get_parent_node(*root, index);

	/* Create and attach the new node */
	new_node = binary_tree_node(parent, value);
	if (parent->left == NULL)
		parent->left = new_node;
	else
		parent->right = new_node;

	/* Reheapify (bubble up) */
	while (new_node->parent && new_node->n > new_node->parent->n)
	{
		swap_values(new_node, new_node->parent);
		new_node = new_node->parent;
	}

	return (new_node);
}

/**
 * binary_tree_size - Measures the size of a binary tree.
 * @tree: Pointer to the root node of the tree.
 *
 * Return: Size of the tree (number of nodes).
 */
size_t binary_tree_size(const binary_tree_t *tree)
{
	if (!tree)
		return (0);
	return (1 + binary_tree_size(tree->left) + binary_tree_size(tree->right));
}

/**
 * binary_tree_find_index - Calculates the position index for a new node.
 * @size: Size of the tree + 1.
 *
 * Return: Index of the new node in a level-order traversal.
 */
size_t binary_tree_find_index(size_t size)
{
	return (size);
}

/**
 * get_parent_node - Finds the parent node for a new node based on index.
 * @root: Pointer to the root node of the tree.
 * @index: Index of the new node in level-order.
 *
 * Return: Pointer to the parent node.
 */
heap_t *get_parent_node(heap_t *root, size_t index)
{
	heap_t *node = root;
	size_t mask = 1 << (sizeof(size_t) * 8 - __builtin_clz(index) - 2);

	while (mask > 1)
	{
		node = (index & mask) ? node->right : node->left;
		mask >>= 1;
	}
	return (node);
}

/**
 * swap_values - Swaps the values of two nodes.
 * @a: First node.
 * @b: Second node.
 */
void swap_values(heap_t *a, heap_t *b)
{
	int temp = a->n;

	a->n = b->n;
	b->n = temp;
}
