#include "binary_trees.h"

/**
 * heap_size - Calculate the size of a heap
 * @root: Pointer to the root node
 *
 * Return: Size of the heap
 */
static size_t heap_size(const heap_t *root)
{
	if (root == NULL)
		return (0);

	return (1 + heap_size(root->left) + heap_size(root->right));
}

/**
 * heapify_up - Maintain max heap property by moving node up
 * @node: Node to heapify up
 *
 * Return: Pointer to the node after heapifying
 */
static heap_t *heapify_up(heap_t *node)
{
	int temp;

	while (node->parent && node->n > node->parent->n)
	{
		/* Swap values */
		temp = node->n;
		node->n = node->parent->n;
		node->parent->n = temp;
		
		/* Move up */
		node = node->parent;
	}

	return (node);
}

/**
 * find_insertion_point - Find where to insert the next node
 * @root: Root of the heap
 * @index: Index of the node to insert (1-based)
 *
 * Return: Pointer to the parent where insertion should happen
 */
static heap_t *find_insertion_point(heap_t *root, size_t index)
{
	char path[64];
	int i, path_len = 0;
	heap_t *current = root;
	size_t temp = index;

	/* Convert index to binary path */
	while (temp > 1)
	{
		path[path_len++] = (temp % 2) ? 'R' : 'L';
		temp /= 2;
	}

	/* Traverse the path (in reverse) to find insertion point */
	for (i = path_len - 2; i >= 0; i--)
	{
		if (path[i] == 'L')
			current = current->left;
		else
			current = current->right;
	}

	return (current);
}

/**
 * heap_insert - Insert a value into a Max Binary Heap
 * @root: Double pointer to the root node of the Heap
 * @value: Value to store in the node to be inserted
 *
 * Return: Pointer to the inserted node, or NULL on failure
 */
heap_t *heap_insert(heap_t **root, int value)
{
	heap_t *new_node, *parent;
	size_t size, index;

	if (root == NULL)
		return (NULL);

	/* If tree is empty, create root */
	if (*root == NULL)
	{
		*root = binary_tree_node(NULL, value);
		return (*root);
	}

	size = heap_size(*root);
	index = size + 1; /* Next position to insert */

	/* Find the parent for the new node */
	parent = find_insertion_point(*root, index);

	/* Create and insert the new node */
	new_node = binary_tree_node(parent, value);
	if (new_node == NULL)
		return (NULL);

	/* Insert as left or right child based on position */
	if (parent->left == NULL)
		parent->left = new_node;
	else
		parent->right = new_node;

	/* Heapify up to maintain max heap property */
	return (heapify_up(new_node));
}