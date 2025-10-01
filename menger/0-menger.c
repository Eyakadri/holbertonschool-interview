#include "menger.h"

/**
 * is_menger_point - Check if a point should be printed in Menger sponge
 * @x: X coordinate
 * @y: Y coordinate
 * @level: Current level
 *
 * Return: 1 if point should be printed, 0 otherwise
 */
static int is_menger_point(int x, int y, int level)
{
	/* Base case: level 0 is always a solid point */
	if (level == 0)
		return (1);

	/* Check if we're in the center third of current level */
	/* If both coordinates are in center third, it's empty */
	if ((x % 3 == 1) && (y % 3 == 1))
		return (0);

	/* Recursively check the next level down */
	return (is_menger_point(x / 3, y / 3, level - 1));
}

/**
 * menger - Draw a 2D Menger sponge
 * @level: Level of the Menger sponge to draw
 *
 * Description: Draws a 2D Menger sponge of specified level.
 * Level 0 is a single '#', level N is 3^N x 3^N pattern.
 */
void menger(int level)
{
	int size, x, y;

	/* Do nothing if level is negative */
	if (level < 0)
		return;

	/* Calculate size: 3^level */
	size = 1;
	for (x = 0; x < level; x++)
		size *= 3;

	/* Draw the sponge */
	for (y = 0; y < size; y++)
	{
		for (x = 0; x < size; x++)
		{
			if (is_menger_point(x, y, level))
				printf("#");
			else
				printf(" ");
		}
		printf("\n");
	}
}
