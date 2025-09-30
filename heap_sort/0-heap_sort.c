#include "sort.h"

/**
 * swap_ints - Swap two integers in an array.
 * @a: The first integer to swap.
 * @b: The second integer to swap.
 */
void swap_ints(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

/**
 * sift_down - Perform sift-down operation on a heap.
 * @array: The array representing the heap.
 * @size: The size of the heap.
 * @start: The starting index of the subtree to sift down.
 * @end: The ending index of the heap.
 */
void sift_down(int *array, size_t size, size_t start, size_t end)
{
	size_t root = start, child, swap;

	while (2 * root + 1 <= end)
	{
		child = 2 * root + 1;
		swap = root;

		if (array[swap] < array[child])
			swap = child;
		if (child + 1 <= end && array[swap] < array[child + 1])
			swap = child + 1;
		if (swap == root)
			return;
		swap_ints(&array[root], &array[swap]);
		print_array(array, size);
		root = swap;
	}
}

/**
 * heapify - Build a max heap from an array.
 * @array: The array to heapify.
 * @size: The size of the array.
 */
void heapify(int *array, size_t size)
{
	int start = (size - 2) / 2;

	while (start >= 0)
	{
		sift_down(array, size, start, size - 1);
		start--;
	}
}

/**
 * heap_sort - Sort an array of integers in ascending order using Heap sort.
 * @array: The array to sort.
 * @size: The size of the array.
 */
void heap_sort(int *array, size_t size)
{
	size_t end;

	if (!array || size < 2)
		return;

	heapify(array, size);

	end = size - 1;
	while (end > 0)
	{
		swap_ints(&array[0], &array[end]);
		print_array(array, size);
		end--;
		sift_down(array, size, 0, end);
	}
}
