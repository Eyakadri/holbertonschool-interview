#include "substring.h"

/**
 * check_in_array - return 1 if 'ans' is not in array 'arr'
 * @arr: an array of integers
 * @len: the length of the array 'arr'
 * @ans: the value to check for
 * Return: 1 if value not found, else 0
 */
int check_in_array(int *arr, int len, int ans)
{
	int i = 0;

	for (i = 0; i < len; i++)
	{
		if (arr[i] == ans)
			return (0);
	}
	return (1);
}

/**
 * check_word - returns true (1) if a word matches a substring
 * @str: a string
 * @word: an array of words
 * Return: 1 if word is a substring of str, 0 otherwise
 */
int check_word(char const *str, char const *word)
{
	int i = 0;

	for (i = 0; *(word + i) != '\0'; i++)
	{
		if (*(str + i) != *(word + i))
			return (0);
	}
	return (1);
}

/**
 * match - find if a substring match occurs at a single location
 * @s: a string
 * @words: an array of words
 * @nb_words: the number of elements in parameter 'words'
 * @word_len: the length of each word
 * Return: 1 if a full match of a substring made of 'words' exists, 0 otherwise
 */
int match(char const *s, char const **words, int nb_words, int word_len)
{
	int *checked;
	int checked_len = 0;
	int found = 0;
	int match = 1;
	int i, j, k;
	int in_array;

	checked = malloc(sizeof(int) * nb_words);

	for (k = 0; k < nb_words; k++)
		checked[k] = -1;

	for (i = 0; i < nb_words; i++)
	{
		found = 0;
		for (j = 0; j < nb_words; j++)
		{
			in_array = check_in_array(checked, checked_len, j);
			if (in_array && check_word((s + (i * word_len)), words[j]))
			{
				checked[checked_len] = j;
				checked_len++;
				found = 1;
				break;
			}
		}
		if (found == 0)
		{
			match = 0;
			break;
		}
	}
	free(checked);
	return (match);
}

/**
 * find_substring - find in 's' substrings made up of the words in 'words'
 * @s: a string
 * @words: an array of words
 * @nb_words: the number of elements in parameter 'words'
 * @n: AUX RETURN VALUE the number of elements in the returned array
 * Return: an array of starting indices of found substrings
 */
int *find_substring(char const *s, char const **words, int nb_words, int *n)
{
	int *result;
	int str_len = 0;
	int word_len = 0;
	int i;

	*n = 0;
	if (s == NULL || words == NULL || *words == NULL || nb_words == 0)
		return (NULL);

	for (i = 0; s[i] != '\0'; i++)
		str_len++;
	for (i = 0; words[0][i] != '\0'; i++)
		word_len++;

	result = malloc(sizeof(int) * str_len);
	if (result == NULL)
		return (NULL);

	for (i = 0; *(s + i) != '\0'; i++)
	{
		if (match(s + i, words, nb_words, word_len))
		{
			result[*n] = i;
			*n = *n + 1;
		}
	}

	if (*n == 0)
	{
		free(result);
		return (NULL);
	}

	return (result);
}
