#include "holberton.h"
#include <stdlib.h>

/**
 * is_digit - checks if a string contains only digits
 * @s: string to check
 * Return: 1 if all digits, 0 otherwise
 */
int is_digit(char *s)
{
	int i = 0;

	if (!s)
		return (0);

	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

/**
 * _strlen - returns the length of a string
 * @s: string
 * Return: length
 */
int _strlen(char *s)
{
	int i = 0;

	while (s[i])
		i++;
	return (i);
}

/**
 * print_error - prints Error and exits
 */
void print_error(void)
{
	char *msg = "Error\n";
	int i = 0;

	while (msg[i])
	{
		_putchar(msg[i]);
		i++;
	}
	exit(98);
}

/**
 * print_number - prints a number given as string (leading zeros stripped)
 * @num: string number
 * @len: length of the string
 */
void print_number(char *num, int len)
{
	int i = 0;

	while (i < len && num[i] == '0')
		i++;
	if (i == len)
		_putchar('0');
	for (; i < len; i++)
		_putchar(num[i]);
	_putchar('\n');
}

/**
 * infinite_mul - multiplies two positive numbers given as strings
 * @num1: first number
 * @num2: second number
 */
void infinite_mul(char *num1, char *num2)
{
	int len1 = _strlen(num1), len2 = _strlen(num2);
	int *result, i, j, carry, n1, n2, sum;
	int len = len1 + len2;
	char *res_str;

	result = malloc(sizeof(int) * len);
	if (!result)
		print_error();

	for (i = 0; i < len; i++)
		result[i] = 0;

	for (i = len1 - 1; i >= 0; i--)
	{
		n1 = num1[i] - '0';
		carry = 0;
		for (j = len2 - 1; j >= 0; j--)
		{
			n2 = num2[j] - '0';
			sum = n1 * n2 + result[i + j + 1] + carry;
			carry = sum / 10;
			result[i + j + 1] = sum % 10;
		}
		result[i + j + 1] += carry;
	}

	/* Convert int array to char array */
	res_str = malloc(sizeof(char) * (len + 1));
	if (!res_str)
	{
		free(result);
		print_error();
	}

	for (i = 0; i < len; i++)
		res_str[i] = result[i] + '0';
	res_str[len] = '\0';

	print_number(res_str, len);

	free(result);
	free(res_str);
}

/**
 * main - Entry point
 * @argc: argument count
 * @argv: argument vector
 * Return: 0 on success, 98 on failure
 */
int main(int argc, char **argv)
{
	if (argc != 3)
		print_error();

	if (!is_digit(argv[1]) || !is_digit(argv[2]))
		print_error();

	infinite_mul(argv[1], argv[2]);

	return (0);
}
