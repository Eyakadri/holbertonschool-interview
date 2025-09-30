#include "palindrome.h"

/**
 * is_palindrome - Checks if a given unsigned integer is a palindrome.
 * @n: The number to check.
 *
 * Return: 1 if n is a palindrome, 0 otherwise.
 */
int is_palindrome(unsigned long n)
{
	unsigned long reversed = 0, original = n;

	/* Reverse the number */
	while (n != 0)
	{
		reversed = reversed * 10 + n % 10;
		n /= 10;
	}

	/* Check if the reversed number matches the original */
	return (original == reversed);
}
