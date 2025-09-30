#include "binary_trees.h"

size_t binary_tree_height(heap_t *node);
void find_last_node(heap_t *node, size_t lvl, heap_t **last);
void replace_root(heap_t **root, heap_t **l, heap_t **r, heap_t **last);
void heapify_down(heap_t **root, heap_t *node, int *cont);
/**
 * heap_extract - Removes and returns the root from a max heap.
 * The root is replaced with the last node in level-order,
 * and the heap is adjusted to maintain the max heap property.
 *
 * @root: Double pointer to the root of the heap
 *
 * Return: The value stored in the extracted root, or 0 on failure
 */
int heap_extract(heap_t **root)
{
	int extracted;
	heap_t *last = NULL, *left = NULL, *right = NULL;
	size_t height, lvl;
	int continue_swap = 1;

	if (!root || !*root)
		return (0);

	extracted = (*root)->n;
	left = (*root)->left;
	right = (*root)->right;

	height = binary_tree_height(*root);
	for (lvl = 0; lvl <= height; lvl++)
		find_last_node(*root, lvl, &last);

	replace_root(root, &left, &right, &last);

	while (last && continue_swap)
		heapify_down(root, last, &continue_swap);

	return (extracted);
}

/**
 * binary_tree_height - Measures the height of a complete binary tree
 * It assumes the left subtree is always the deepest due to completeness
 *
 * @node: Pointer to the current node
 *
 * Return: Height from the given node to the leaf
 */
size_t binary_tree_height(heap_t *node)
{
	if (!node)
		return (0);
	return (1 + binary_tree_height(node->left));
}

/**
 * find_last_node - Traverses tree in level order to locate the last node
 * Used to find the node that will replace the root during extraction
 *
 * @node: Pointer to the current node
 * @lvl: Level depth to check
 * @last: Double pointer to store the address of the last node found
 */
void find_last_node(heap_t *node, size_t lvl, heap_t **last)
{
	if (!node)
		return;

	if (lvl == 0)
		*last = node;

	find_last_node(node->left, lvl - 1, last);
	find_last_node(node->right, lvl - 1, last);
}

/**
 * replace_root - Frees the original root node and sets a new root
 * using the last level-order node; reconnects children as needed
 *
 * @root: Double pointer to the heap root
 * @l: Double pointer to original left child of root
 * @r: Double pointer to original right child of root
 * @last: Double pointer to the node replacing the root
 */
void replace_root(heap_t **root, heap_t **l, heap_t **r, heap_t **last)
{
	if (*last == *root)
	{
		free(*root);
		*root = NULL;
		return;
	}

	if ((*last)->parent->left == *last)
		(*last)->parent->left = NULL;
	else
		(*last)->parent->right = NULL;

	(*last)->parent = NULL;
	free(*root);
	*root = *last;

	if (*l != *last)
	{
		(*last)->left = *l;
		if (*l)
			(*l)->parent = *last;
	}
	if (*r != *last)
	{
		(*last)->right = *r;
		if (*r)
			(*r)->parent = *last;
	}
}

/**
 * heapify_down - Adjusts the heap from the root downward
 * Ensures max heap rules are preserved after replacement
 *
 * @root: Double pointer to the current root of the heap
 * @node: Pointer to the node from which to begin the heap fix
 * @cont: Pointer to flag whether swapping should continue
 */
void heapify_down(heap_t **root, heap_t *node, int *cont)
{
	heap_t *max_node = node;
	heap_t *left = node->left;
	heap_t *right = node->right;

	if (left && left->n > max_node->n)
		max_node = left;
	if (right && right->n > max_node->n)
		max_node = right;

	if (max_node == node)
	{
		*cont = 0;
		return;
	}

	if (node->parent)
	{
		if (node->parent->left == node)
			node->parent->left = max_node;
		else
			node->parent->right = max_node;
	}
	else
		*root = max_node;

	max_node->parent = node->parent;
	node->left = max_node->left;
	if (max_node->left)
		max_node->left->parent = node;
	node->right = max_node->right;
	if (max_node->right)
		max_node->right->parent = node;

	if (max_node == left)
	{
		max_node->left = node;
		max_node->right = right;
		if (right)
			right->parent = max_node;
	}
	else
	{
		max_node->right = node;
		max_node->left = left;
		if (left)
			left->parent = max_node;
	}

	node->parent = max_node;
}
