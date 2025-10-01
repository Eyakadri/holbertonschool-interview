# Heap Insert

This project implements binary tree node creation and max binary heap insertion operations.

## Files

- `binary_trees.h` - Header file with structure definitions and function prototypes
- `0-binary_tree_node.c` - Creates a binary tree node
- `1-heap_insert.c` - Inserts a value into a Max Binary Heap
- `binary_tree_print.c` - Utility function to print binary trees

## Functions

### binary_tree_node
Creates a binary tree node with the given parent and value.

### heap_insert
Inserts a value into a Max Binary Heap, maintaining the heap property and complete binary tree structure.

## Compilation

```bash
gcc -Wall -Wextra -Werror -pedantic binary_tree_print.c 0-main.c 0-binary_tree_node.c -o 0-node
gcc -Wall -Wextra -Werror -pedantic binary_tree_print.c 1-main.c 1-heap_insert.c 0-binary_tree_node.c -o 1-heap_insert
```