#include "search.h"

/**
 * linear_skip - Searches for a value in a sorted skip list of integers
 * @list: Pointer to the head of the skip list to search in
 * @value: Value to search for
 *
 * Return: Pointer to the first node where value is located, or NULL
 */
skiplist_t *linear_skip(skiplist_t *list, int value)
{
	skiplist_t *current, *prev;

	if (list == NULL)
		return (NULL);

	current = list;
	prev = NULL;

	/* Use express lane to find the correct section */
	while (current->express != NULL)
	{
		printf("Value checked at index [%lu] = [%d]\n", current->index, current->n);
		
		if (current->express->n >= value)
			break;
		
		prev = current;
		current = current->express;
	}

	/* If we're at the last express lane node, check its value */
	if (current->express == NULL)
	{
		printf("Value checked at index [%lu] = [%d]\n", current->index, current->n);
		
		/* Find the end of the list to determine the range */
		while (current->next != NULL)
			current = current->next;
		
		printf("Value found between indexes [%lu] and [%lu]\n",
			prev ? prev->index : list->index, current->index);
		
		/* Go back to start of search section */
		current = prev ? prev : list;
	}
	else
	{
		printf("Value found between indexes [%lu] and [%lu]\n",
			current->index, current->express->index);
	}

	/* Linear search in the identified section */
	while (current != NULL)
	{
		printf("Value checked at index [%lu] = [%d]\n", current->index, current->n);
		
		if (current->n == value)
			return (current);
		
		if (current->n > value)
			break;
		
		current = current->next;
	}

	return (NULL);
}
