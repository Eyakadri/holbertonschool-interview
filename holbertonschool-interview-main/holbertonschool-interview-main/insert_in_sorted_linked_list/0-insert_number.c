#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "lists.h"

/**
 * insert_node - Inserts a new node into a sorted singly linked list
 * @head: Pointer to the pointer to the first node of the list
 * @number: The number to insert into the list
 *
 * Return: Pointer to the new node, or NULL if memory allocation fails
 */
listint_t *insert_node(listint_t **head, int number)
{
	listint_t *new;
	listint_t *current;

	new = malloc(sizeof(listint_t));
	if (new == NULL)
		return (NULL);

	new->n = number;
	new->next = NULL;

	if (*head == NULL || (*head)->n >= number)
	{
		new->next = *head;
		*head = new;
		return (new);
	}

	current = *head;
	while (current->next != NULL && current->next->n < number)
		current = current->next;

	new->next = current->next;
	current->next = new;

	return (new);
}
