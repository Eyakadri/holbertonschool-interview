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
 * print_error - prints Error and exits with status 98
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
 * print_number - prints a number string (skip leading zeros)
 * @num: string number
 * @len: length of string
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
 * multiply - performs multiplication and fills result array
 * @num1: first number string
 * @num2: second number string
 * @len1: length of num1
 * @len2: length of num2
 * @result: integer array to store multiplication result
 */
void multiply(char *num1, char *num2, int len1, int len2, int *result)
{
	int i, j, n1, n2, sum, carry;

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
}

/**
 * infinite_mul - main function to multiply two large positive numbers
 * @num1: first number string
 * @num2: second number string
 */
void infinite_mul(char *num1, char *num2)
{
	int len1 = _strlen(num1);
	int len2 = _strlen(num2);
	int len = len1 + len2;
	int *result;
	char *res_str;
	int i;

	result = malloc(sizeof(int) * len);
	if (!result)
		print_error();

	for (i = 0; i < len; i++)
		result[i] = 0;

	multiply(num1, num2, len1, len2, result);

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
 * Return: 0 on success, exits 98 on failure
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
