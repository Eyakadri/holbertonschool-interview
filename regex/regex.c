#include "regex.h"

/**
 * regex_match - Checks whether a given pattern matches a given string.
 * @str: The string to be matched.
 * @pattern: The pattern to match against.
 *
 * Return: 1 if the pattern matches the string, 0 otherwise.
 */
int regex_match(char const *str, char const *pattern)
{
	int first_match;

	if (!str || !pattern)
		return (0);

	if (!*pattern)
		return (!*str);

	first_match = (*str && (*pattern == *str || *pattern == '.'));

	if (*(pattern + 1) == '*')
	{
		return (regex_match(str, pattern + 2) ||
			(first_match && regex_match(str + 1, pattern)));
	}
	else
	{
		return (first_match && regex_match(str + 1, pattern + 1));
	}
}
