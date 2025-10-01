#include "substring.h"
#include <stdlib.h>
#include <string.h>

/**
 * str_len - Calculate string length
 * @s: String to measure
 *
 * Return: Length of string
 */
static int str_len(char const *s)
{
	int len = 0;

	if (!s)
		return (0);
	while (s[len])
		len++;
	return (len);
}

/**
 * str_cmp - Compare two strings up to n characters
 * @s1: First string
 * @s2: Second string
 * @n: Number of characters to compare
 *
 * Return: 0 if equal, non-zero if different
 */
static int str_cmp(char const *s1, char const *s2, int n)
{
	int i;

	for (i = 0; i < n; i++)
	{
		if (s1[i] != s2[i])
			return (1);
	}
	return (0);
}

/**
 * is_valid_substring - Check if substring is valid concatenation
 * @s: Start of substring
 * @words: Array of words
 * @nb_words: Number of words
 * @word_len: Length of each word
 *
 * Return: 1 if valid, 0 if not
 */
static int is_valid_substring(char const *s, char const **words,
			      int nb_words, int word_len)
{
	int *used;
	int i, j, found;

	used = calloc(nb_words, sizeof(int));
	if (!used)
		return (0);

	for (i = 0; i < nb_words; i++)
	{
		found = 0;
		for (j = 0; j < nb_words; j++)
		{
			if (!used[j] &&
			    !str_cmp(s + i * word_len, words[j], word_len))
			{
				used[j] = 1;
				found = 1;
				break;
			}
		}
		if (!found)
		{
			free(used);
			return (0);
		}
	}
	free(used);
	return (1);
}

/**
 * find_substring - Find all substrings containing concatenated words
 * @s: String to scan
 * @words: Array of words
 * @nb_words: Number of words
 * @n: Address to store number of results
 *
 * Return: Array of indices or NULL
 */
int *find_substring(char const *s, char const **words, int nb_words, int *n)
{
	int s_len, word_len, total_len, *result, *temp;
	int i, count = 0, capacity = 10;

	*n = 0;
	if (!s || !words || nb_words <= 0)
		return (NULL);

	s_len = str_len(s);
	word_len = str_len(words[0]);
	total_len = word_len * nb_words;

	if (s_len < total_len)
		return (NULL);

	result = malloc(capacity * sizeof(int));
	if (!result)
		return (NULL);

	for (i = 0; i <= s_len - total_len; i++)
	{
		if (is_valid_substring(s + i, words, nb_words, word_len))
		{
			if (count >= capacity)
			{
				capacity *= 2;
				temp = realloc(result, capacity * sizeof(int));
				if (!temp)
				{
					free(result);
					return (NULL);
				}
				result = temp;
			}
			result[count++] = i;
		}
	}

	*n = count;
	if (count == 0)
	{
		free(result);
		return (NULL);
	}

	return (result);
}
