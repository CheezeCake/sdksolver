#include <stdint.h>
#include "solve.h"

int solve(Grid *grid, int p)
{
	int i, j, k;

	if(p == (grid->size*grid->size))
		return VERIF(grid);
	
	i = p/grid->size;
	j = p%grid->size;

	if(grid->grid[i][j] == ' ')
	{
		for(k = 1; k <= grid->size; k++)
		{
			grid->grid[i][j] = CHAR(k);

			if(VERIF(grid) && solve(grid, p+1))
				return 1;

			grid->grid[i][j] = ' ';
		}
	}
	else
	{
		if(solve(grid, p+1))
			return 1;
	}

	return 0;
}

int lines(Grid *grid)
{
	int i, j, v;
	for(i = 0; i < grid->size; i++)
	{
		uint64_t mask = 0;
		for(j = 0; j < grid->size; j++)
		{
			if(grid->grid[i][j] != ' ')
			{
				v = INT(grid->grid[i][j])-1;
				if((mask | (1<<v)) == mask)
					return 0;

				mask |= (1<<v);
			}
		}
	}

	return 1;
}

int columns(Grid *grid)
{
	int i, j, v;
	for(i = 0; i < grid->size; i++)
	{
		uint64_t mask = 0;
		for(j = 0; j < grid->size; j++)
		{
			if(grid->grid[j][i] != ' ')
			{
				v = INT(grid->grid[j][i])-1;
				if((mask | (1<<v)) == mask)
					return 0;

				mask |= (1<<v);
			}
		}
	}

	return 1;
}

int regions(Grid *grid)
{
	int i, j, k, l;
	int nb_regions = grid->size/grid->region_size;

	for(i = 0; i < nb_regions; i++)
	{
		for(j = 0; j < nb_regions; j++)
		{
			uint64_t mask = 0;
			for(k = 0; k < grid->region_size; k++)
			{
				for(l = 0; l < grid->region_size; l++)
				{
					int a, b, v;
					a = (i*grid->region_size)+k;
					b = (j*grid->region_size)+l;
					if(grid->grid[a][b] != ' ')
					{
						v = INT(grid->grid[a][b])-1;

						if((mask | (1<<v)) == mask)
							return 0;

						mask |= (1<<v);
					}
				}
			}
		}
	}

	return 1;
}
