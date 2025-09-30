#include "slide_line.h"

/**
 * slide_line - Slides and merges an array of integers to the left or right.
 * @line: Pointer to the array of integers.
 * @size: Number of elements in the array.
 * @direction: Direction to slide and merge (SLIDE_LEFT or SLIDE_RIGHT).
 * Return: 1 on success, 0 on failure.
 */
int slide_line(int *line, size_t size, int direction)
{
    size_t i, j;
    int merged = 0;

    if (line == NULL || (direction != SLIDE_LEFT && direction != SLIDE_RIGHT))
        return 0;

    if (direction == SLIDE_LEFT)
    {
        for (i = 0, j = 0; i < size; i++)
        {
            if (line[i] != 0)
            {
                if (j > 0 && line[j - 1] == line[i] && !merged)
                {
                    line[j - 1] += line[i];
                    merged = 1;
                }
                else
                {
                    if (j != i)
                        line[j] = line[i];
                    j++;
                    merged = 0;
                }
            }
        }
        while (j < size)
            line[j++] = 0;
    }
    else if (direction == SLIDE_RIGHT)
    {
        for (i = size - 1, j = size - 1; (int)i >= 0; i--)
        {
            if (line[i] != 0)
            {
                if (j < size - 1 && line[j + 1] == line[i] && !merged)
                {
                    line[j + 1] += line[i];
                    merged = 1;
                }
                else
                {
                    if (j != i)
                        line[j] = line[i];
                    j--;
                    merged = 0;
                }
            }
        }
        while ((int)j >= 0)
            line[j--] = 0;
    }

    return 1;
}
