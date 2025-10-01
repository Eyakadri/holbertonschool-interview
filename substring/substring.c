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
 * add_index_to_result - Add index to result array, resize if needed
 * @result: Current result array
 * @count: Pointer to current count
 * @capacity: Pointer to current capacity
 * @index: Index to add
 *
 * Return: Updated result array or NULL on failure
 */
static int *add_index_to_result(int *result, int *count, int *capacity, int index)
{
	int *temp;

	if (*count >= *capacity)
	{
		*capacity *= 2;
		temp = realloc(result, *capacity * sizeof(int));
		if (!temp)
		{
			free(result);
			return (NULL);
		}
		result = temp;
	}
	result[(*count)++] = index;
	return (result);
}

/**
 * search_substrings - Search for valid substrings in the string
 * @s: String to scan
 * @words: Array of words
 * @nb_words: Number of words
 * @params: Array containing [s_len, word_len, total_len]
 * @result_info: Array containing [count, capacity]
 * @result: Result array
 *
 * Return: Updated result array or NULL on failure
 */
static int *search_substrings(char const *s, char const **words, int nb_words,
	int *params, int *result_info, int *result)
{
	int i, s_len = params[0], total_len = params[2], word_len = params[1];

	for (i = 0; i <= s_len - total_len; i++)
	{
		if (is_valid_substring(s + i, words, nb_words, word_len))
		{
			result = add_index_to_result(result, &result_info[0],
				&result_info[1], i);
			if (!result)
				return (NULL);
		}
	}
	return (result);
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
	int params[3], result_info[2] = {0, 10}, *result;

	*n = 0;
	if (!s || !words || nb_words <= 0)
		return (NULL);

	params[0] = str_len(s);
	params[1] = str_len(words[0]);
	params[2] = params[1] * nb_words;

	if (params[0] < params[2])
		return (NULL);

	result = malloc(result_info[1] * sizeof(int));
	if (!result)
		return (NULL);

	result = search_substrings(s, words, nb_words, params, result_info, result);
	if (!result)
		return (NULL);

	*n = result_info[0];
	if (result_info[0] == 0)
	{
		free(result);
		return (NULL);
	}
	return (result);
}
