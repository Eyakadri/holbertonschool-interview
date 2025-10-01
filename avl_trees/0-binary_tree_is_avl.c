#include "binary_trees.h"

/**
 * binary_tree_height - Measures the height of a binary tree
 * @tree: Pointer to the root node of the tree to measure the height
 *
 * Return: Height of the tree, 0 if tree is NULL
 */
static int binary_tree_height(const binary_tree_t *tree)
{
	int left_height, right_height;

	if (tree == NULL)
		return (0);

	left_height = binary_tree_height(tree->left);
	right_height = binary_tree_height(tree->right);

	return (1 + (left_height > right_height ? left_height : right_height));
}

/**
 * is_bst_helper - Helper function to check if tree is a valid BST
 * @tree: Pointer to the root node of the tree to check
 * @min: Minimum value allowed for current node
 * @max: Maximum value allowed for current node
 *
 * Return: 1 if tree is a valid BST, 0 otherwise
 */
static int is_bst_helper(const binary_tree_t *tree, int min, int max)
{
	if (tree == NULL)
		return (1);

	if (tree->n <= min || tree->n >= max)
		return (0);

	return (is_bst_helper(tree->left, min, tree->n) &&
		is_bst_helper(tree->right, tree->n, max));
}

/**
 * is_bst - Check if a binary tree is a valid BST
 * @tree: Pointer to the root node of the tree to check
 *
 * Return: 1 if tree is a valid BST, 0 otherwise
 */
static int is_bst(const binary_tree_t *tree)
{
	if (tree == NULL)
		return (1);

	return (is_bst_helper(tree, -2147483648, 2147483647));
}

/**
 * binary_tree_is_avl - Checks if a binary tree is a valid AVL Tree
 * @tree: Pointer to the root node of the tree to check
 *
 * Return: 1 if tree is a valid AVL Tree, and 0 otherwise
 */
int binary_tree_is_avl(const binary_tree_t *tree)
{
	int left_height, right_height, balance_factor;

	if (tree == NULL)
		return (0);

	/* Check if it's a valid BST */
	if (!is_bst(tree))
		return (0);

	/* Get heights of left and right subtrees */
	left_height = tree->left ? binary_tree_height(tree->left) : 0;
	right_height = tree->right ? binary_tree_height(tree->right) : 0;

	/* Calculate balance factor */
	balance_factor = left_height - right_height;

	/* Check if balance factor is within AVL tree range (-1, 0, 1) */
	if (balance_factor < -1 || balance_factor > 1)
		return (0);

	/* Recursively check left and right subtrees */
	if (tree->left && !binary_tree_is_avl(tree->left))
		return (0);

	if (tree->right && !binary_tree_is_avl(tree->right))
		return (0);

	return (1);
}
