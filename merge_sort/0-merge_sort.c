#include "sort.h"

/**
 * merge_sort - Sorts an array using merge sort algorithm (top-down)
 * @array: The array to be sorted
 * @size: Size of the array
 */
void merge_sort(int *array, size_t size)
{
	int *tmp;

	if (!array || size < 2)
		return;

	tmp = malloc(sizeof(int) * size);
	if (!tmp)
		return;

	split_merge(array, tmp, 0, size - 1);
	free(tmp);
}

/**
 * split_merge - Recursively splits and merges array
 * @array: Original array
 * @tmp: Temp buffer for merging
 * @start: Starting index
 * @end: Ending index
 */
void split_merge(int *array, int *tmp, size_t start, size_t end)
{
	size_t mid;

	if (start >= end)
		return;

	mid = start + (end - start + 1) / 2 - 1;

	split_merge(array, tmp, start, mid);
	split_merge(array, tmp, mid + 1, end);

	printf("Merging...\n");
	printf("[left]: ");
	print_array(array + start, mid - start + 1);
	printf("[right]: ");
	print_array(array + mid + 1, end - mid);

	do_merge(array, tmp, start, mid, end);

	printf("[Done]: ");
	print_array(array + start, end - start + 1);
}

/**
 * do_merge - Merges two sorted parts of array
 * @array: Original array
 * @tmp: Temp buffer
 * @start: Start index
 * @mid: Middle index
 * @end: End index
 */
void do_merge(int *array, int *tmp, size_t start, size_t mid, size_t end)
{
	size_t i = start, j = mid + 1, k = start;

	while (i <= mid && j <= end)
	{
		if (array[i] <= array[j])
			tmp[k++] = array[i++];
		else
			tmp[k++] = array[j++];
	}

	while (i <= mid)
		tmp[k++] = array[i++];

	while (j <= end)
		tmp[k++] = array[j++];

	for (i = start; i <= end; i++)
		array[i] = tmp[i];
}
