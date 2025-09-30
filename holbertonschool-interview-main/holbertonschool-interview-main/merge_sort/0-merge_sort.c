#include "sort.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * merge - Merges two sub-arrays into a sorted array
 * @array: The original array
 * @temp: Temporary array for merging
 * @left: Starting index of the left sub-array
 * @mid: Ending index of the left sub-array
 * @right: Ending index of the right sub-array
 */
void merge(int *array, int *temp, size_t left, size_t mid, size_t right)
{
	size_t i = left, j = mid, k = left;

	printf("Merging...\n");
	printf("[left]: ");
	print_array(array + left, mid - left);
	printf("[right]: ");
	print_array(array + mid, right - mid);

	while (i < mid && j < right)
	{
		if (array[i] <= array[j])
			temp[k++] = array[i++];
		else
			temp[k++] = array[j++];
	}

	while (i < mid)
		temp[k++] = array[i++];

	while (j < right)
		temp[k++] = array[j++];

	for (i = left; i < right; i++)
		array[i] = temp[i];

	printf("[Done]: ");
	print_array(array + left, right - left);
}

/**
 * merge_sort_recursive - Recursively sorts an array using merge sort
 * @array: The array to sort
 * @temp: Temporary array for merging
 * @left: Starting index of the sub-array
 * @right: Ending index of the sub-array
 */
void merge_sort_recursive(int *array, int *temp, size_t left, size_t right)
{
	if (right - left > 1)
	{
		size_t mid = left + (right - left) / 2;

		merge_sort_recursive(array, temp, left, mid);
		merge_sort_recursive(array, temp, mid, right);
		merge(array, temp, left, mid, right);
	}
}

/**
 * merge_sort - Sorts an array of integers in ascending order using merge sort
 * @array: The array to sort
 * @size: The size of the array
 */
void merge_sort(int *array, size_t size)
{
	int *temp;

	if (size < 2 || !array)
		return;

	temp = malloc(sizeof(int) * size);
	if (!temp)
		return;

	merge_sort_recursive(array, temp, 0, size);

	free(temp);
}
