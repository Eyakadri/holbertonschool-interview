#include "menger.h"
#include <math.h>
#include <stdio.h>

/**
 * is_blank - Check if a position in the Menger sponge should be blank
 * @x: Row index
 * @y: Column index
 *
 * Return: 1 if the position should be blank, 0 otherwise
 */
int is_blank(int x, int y)
{
	while (x > 0 || y > 0)
	{
		if (x % 3 == 1 && y % 3 == 1)
			return (1);
		x /= 3;
		y /= 3;
	}
	return (0);
}

/**
 * menger - Draw a 2D Menger sponge at a given level
 * @level: The level of the Menger sponge
 */
void menger(int level)
{
	int size, x, y;

	if (level < 0)
		return;

	size = pow(3, level);
	for (x = 0; x < size; x++)
	{
		for (y = 0; y < size; y++)
		{
			if (is_blank(x, y))
				printf(" ");
			else
				printf("#");
		}
		printf("\n");
	}
}
