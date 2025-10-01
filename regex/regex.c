#include "regex.h"

/**
 * regex_match - Check if pattern matches string
 * @str: String to check
 * @pattern: Pattern to match against
 *
 * Return: 1 if pattern matches, 0 otherwise
 */
int regex_match(char const *str, char const *pattern)
{
	/* Base case: if pattern is empty, string must also be empty */
	if (*pattern == '\0')
		return (*str == '\0');

	/* Check if next character in pattern is '*' */
	if (*(pattern + 1) == '*')
	{
		/* Case 1: Match zero occurrences of preceding character */
		if (regex_match(str, pattern + 2))
			return (1);

		/* Case 2: Match one or more occurrences */
		/* First character must match (either exact match or '.') */
		if (*str != '\0' && (*pattern == '.' || *pattern == *str))
		{
			/* Try matching more characters with the same pattern */
			return (regex_match(str + 1, pattern));
		}

		/* No match possible */
		return (0);
	}

	/* No '*' following current pattern character */
	/* Current characters must match and continue recursively */
	if (*str != '\0' && (*pattern == '.' || *pattern == *str))
		return (regex_match(str + 1, pattern + 1));

	/* No match */
	return (0);
}
