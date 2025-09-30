#include <stdio.h>
#include <stdlib.h>
#include "lists.h"

/**
 * is_prime - Checks if a number is prime.
 * @num: The number to check.
 *
 * Return: 1 if prime, 0 otherwise.
 */
int is_prime(int num)
{
	int i;

	if (num < 2)
		return (0);
	for (i = 2; i * i <= num; i++)
	{
		if (num % i == 0)
			return (0);
	}
	return (1);
}

/**
 * reverse_list - Reverses the first half of a linked list.
 * @head: Pointer to the head of the list.
 * @mid: Pointer to store the middle node.
 *
 * Return: Pointer to the reversed first half.
 */
listint_t *reverse_list(listint_t *head, listint_t **mid)
{
	listint_t *prev = NULL, *temp;
	listint_t *slow = head, *fast = head;

	while (fast && fast->next)
	{
		fast = fast->next->next;
		temp = slow->next;
		slow->next = prev;
		prev = slow;
		slow = temp;
	}

	*mid = slow;
	return (prev);
}

/**
 * is_palindrome - Checks if a linked list is a palindrome.
 * @head: Double pointer to the head of the linked list.
 *
 * Return: 1 if palindrome, 0 otherwise.
 */
int is_palindrome(listint_t **head)
{
	listint_t *mid, *rev_half;
	int count = 0;
	listint_t *temp = *head;

	if (*head == NULL)
		return (1);

	/* Count the length of the list */
	while (temp)
	{
		count++;
		temp = temp->next;
	}

	/* If the count is prime, return 0 */
	if (is_prime(count))
		return (0);

	/* Reverse the first half of the list */
	rev_half = reverse_list(*head, &mid);

	/* If the list has an odd number of elements, move mid one step forward */
	if (count % 2 != 0)
		mid = mid->next;

	/* Compare the reversed first half with the second half */
	while (rev_half && mid)
	{
		if (rev_half->n != mid->n)
			return (0);
		rev_half = rev_half->next;
		mid = mid->next;
	}

	return (1);
}
