#include "holberton.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>


/**
 * is_digit - checks if a string contains only digits
 * @s: string to check
 * Return: 1 if all digits, 0 otherwise
 */
int is_digit(char *s)
{
	while (*s)
	{
		if (*s < '0' || *s > '9')
			return (0);
		s++;
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
	int len = 0;

	while (s[len])
		len++;
	return (len);
}

/**
 * print_result - prints an array of digits as a number
 * @res: result array
 * @len: length of result
 */
void print_result(int *res, int len)
{
	int i = 0, started = 0;

	while (i < len)
	{
		if (res[i] != 0)
			started = 1;
		if (started)
			_putchar(res[i] + '0');
		i++;
	}
	if (!started)
		_putchar('0');
	_putchar('\n');
}

/**
 * main - multiplies two positive numbers
 * @argc: argument count
 * @argv: argument vector
 * Return: 0 on success, 98 on error
 */
int main(int argc, char *argv[])
{
	char *num1, *num2;
	int len1, len2, *res, i, j, mul, sum;

	if (argc != 3 || !is_digit(argv[1]) || !is_digit(argv[2]))
	{
		write(1, "Error\n", 6);
		exit(98);
	}

	num1 = argv[1];
	num2 = argv[2];
	len1 = _strlen(num1);
	len2 = _strlen(num2);
	res = calloc(len1 + len2, sizeof(int));
	if (!res)
		exit(98);

	for (i = len1 - 1; i >= 0; i--)
	{
		for (j = len2 - 1; j >= 0; j--)
		{
			mul = (num1[i] - '0') * (num2[j] - '0');
			sum = mul + res[i + j + 1];
			res[i + j] += sum / 10;
			res[i + j + 1] = sum % 10;
		}
	}

	print_result(res, len1 + len2);
	free(res);
	return (0);
}
