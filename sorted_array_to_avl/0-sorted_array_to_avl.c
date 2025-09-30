#include "binary_trees.h"

/**
 * create_avl_from_sorted_array - Builds an AVL tree
 * @array: Pointer to the first element of the array segment.
 * @start: Starting index of the segment.
 * @end: Ending index of the segment.
 * @parent: Pointer to the parent node.
 * Return: Pointer to the root node of the created subtree.
 */
avl_t *create_avl_from_sorted_array(int *array, int start,
	int end, avl_t *parent)
{
	avl_t *root;
	int mid;

	if (start > end)
		return (NULL);

	mid = (start + end) / 2;
	root = malloc(sizeof(avl_t));
	if (root == NULL)
		return (NULL);

	root->n = array[mid];
	root->parent = parent;
	root->left = create_avl_from_sorted_array(array, start, mid - 1, root);
	root->right = create_avl_from_sorted_array(array, mid + 1, end, root);

	return (root);
}

/**
 * sorted_array_to_avl - Builds an AVL tree from a sorted array.
 * @array: Pointer to the first element of the array to be converted.
 * @size: Number of elements in the array.
 * Return: Pointer to the root node
 */
avl_t *sorted_array_to_avl(int *array, size_t size)
{
	if (array == NULL || size == 0)
		return (NULL);

	return (create_avl_from_sorted_array(array, 0, size - 1, NULL));
}
