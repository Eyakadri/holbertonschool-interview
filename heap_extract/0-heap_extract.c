#include "binary_trees.h"
#include <stdlib.h>

/**
 * swap_values - Swap values of two nodes.
 * @a: First node
 * @b: Second node
 */
void swap_values(heap_t *a, heap_t *b)
{
	int tmp;

	tmp = a->n;
	a->n = b->n;
	b->n = tmp;
}

/**
 * heapify_down - Heapify the node down to maintain heap property.
 * @root: Pointer to the root node
 */
void heapify_down(heap_t *root)
{
	heap_t *largest = root;

	while (1)
	{
		heap_t *left = largest->left, *right = largest->right;
		heap_t *max_node = largest;

		if (left && left->n > max_node->n)
			max_node = left;
		if (right && right->n > max_node->n)
			max_node = right;

		if (max_node == largest)
			break;

		swap_values(largest, max_node);
		largest = max_node;
	}
}

/**
 * get_height - Get the height of a binary tree.
 * @root: Pointer to the root node
 * Return: Height of the tree
 */
int get_height(heap_t *root)
{
	int left, right;

	if (!root)
		return (0);

	left = get_height(root->left);
	right = get_height(root->right);

	return ((left > right ? left : right) + 1);
}

/**
 * get_last_node - Find the last node in level order.
 * @root: Pointer to the root node
 * @height: Current height
 * Return: Pointer to last node
 */
heap_t *get_last_node(heap_t *root, int height)
{
	heap_t *node;

	if (!root || height < 1)
		return (NULL);
	if (height == 1)
		return (root);

	node = get_last_node(root->right, height - 1);
	if (node)
		return (node);
	return (get_last_node(root->left, height - 1));
}

/**
 * heap_extract - Extracts the root from a Max Binary Heap.
 * @root: Double pointer to root node
 * Return: Value of extracted node, or 0 on failure
 */
int heap_extract(heap_t **root)
{
	heap_t *last;
	int value, height;

	if (!root || !*root)
		return (0);

	value = (*root)->n;
	if (!(*root)->left && !(*root)->right)
	{
		free(*root);
		*root = NULL;
		return (value);
	}

	height = get_height(*root);
	last = get_last_node(*root, height);

	if (last == last->parent->right)
		last->parent->right = NULL;
	else
		last->parent->left = NULL;

	(*root)->n = last->n;
	free(last);

	heapify_down(*root);

	return (value);
}

