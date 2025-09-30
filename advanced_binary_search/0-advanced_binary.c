#include <stdio.h>
#include "search_algos.h"

/**
 * advanced_binary_recursive - helper function for recursive binary search
 * @array: pointer to the first element of the array
 * @left: left index of the sub-array
 * @right: right index of the sub-array
 * @value: value to search for
 * Return: index of the first occurrence of value, or -1 if not found
 */
int advanced_binary_recursive(int *array, size_t left, size_t right, int value)
{
	size_t i, mid;

	if (right >= left)
	{
		printf("Searching in array: ");
		for (i = left; i <= right; i++)
		{
			printf("%d", array[i]);
			if (i < right)
				printf(", ");
		}
		printf("\n");

		mid = left + (right - left) / 2;

		/* If value is at mid and it's the first occurrence */
		if (array[mid] == value && (mid == left || array[mid - 1] != value))
			return (mid);

		/* If value is smaller than or equal to mid, search left */
		if (array[mid] >= value)
			return (advanced_binary_recursive(array, left, mid, value));

		/* Else search right */
		return (advanced_binary_recursive(array, mid + 1, right, value));
	}

	return (-1);
}

/**
 * advanced_binary - searches for a value in a sorted array of integers
 * @array: pointer to the first element of the array to search in
 * @size: number of elements in the array
 * @value: value to search for
 * Return: index where value is located, or -1 if not found
 */
int advanced_binary(int *array, size_t size, int value)
{
	if (array == NULL || size == 0)
		return (-1);

	return (advanced_binary_recursive(array, 0, size - 1, value));
}
