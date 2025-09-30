#include "search.h"

/**
 * linear_skip - Searches for a value in a sorted skip list of integers
 * @list: Pointer to the head of the skip list
 * @value: Value to search for
 *
 * Return: Pointer to the node where value is located, or NULL if not found
 */
skiplist_t *linear_skip(skiplist_t *list, int value)
{
	skiplist_t *start = list, *end = NULL;

	if (!list)
		return (NULL);

	while (start->express && start->express->n < value)
	{
		printf("Value checked at index [%lu] = [%d]\n",
			start->express->index, start->express->n);
		start = start->express;
	}

	if (start->express)
	{
		end = start->express;
		printf("Value checked at index [%lu] = [%d]\n", end->index, end->n);
	}
	else
	{
		end = start;
		while (end->next)
			end = end->next;
	}

	printf("Value found between indexes [%lu] and [%lu]\n",
		start->index, end->index);

	while (start && start->index <= end->index)
	{
		printf("Value checked at index [%lu] = [%d]\n", start->index, start->n);
		if (start->n == value)
			return (start);
		start = start->next;
	}

	return (NULL);
}
