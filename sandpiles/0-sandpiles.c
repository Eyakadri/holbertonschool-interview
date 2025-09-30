#include "sandpiles.h"
#include <stdio.h>

/**
 * print_grid - Prints a 3x3 grid
 * @grid: The grid to print
 */
static void print_grid(int grid[3][3])
{
	int i, j;

	printf("=\n");
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (j)
				printf(" ");
			printf("%d", grid[i][j]);
		}
		printf("\n");
	}
}

/**
 * is_stable - Checks if the sandpile is stable
 * @grid: The sandpile to check
 * Return: 1 if stable, 0 otherwise
 */
int is_stable(int grid[3][3])
{
	int i, j;

	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++)
			if (grid[i][j] > 3)
				return (0);
	return (1);
}

/**
 * sandpiles_sum - Computes the sum of two sandpiles
 * @grid1: First sandpile (result will be stored here)
 * @grid2: Second sandpile
 */
void sandpiles_sum(int grid1[3][3], int grid2[3][3])
{
	int i, j;
	int temp[3][3];

	/* Sum the two grids */
	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++)
			grid1[i][j] += grid2[i][j];

	/* Topple until stable */
	while (!is_stable(grid1))
	{
		print_grid(grid1);

		/* Copy grid1 to temp and reset grid1 */
		for (i = 0; i < 3; i++)
			for (j = 0; j < 3; j++)
				temp[i][j] = grid1[i][j];

		for (i = 0; i < 3; i++)
		{
			for (j = 0; j < 3; j++)
			{
				if (temp[i][j] > 3)
				{
					grid1[i][j] -= 4;
					if (i > 0)
						grid1[i - 1][j] += 1;
					if (i < 2)
						grid1[i + 1][j] += 1;
					if (j > 0)
						grid1[i][j - 1] += 1;
					if (j < 2)
						grid1[i][j + 1] += 1;
				}
			}
		}
	}
}
