#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "grid.h"

void create_grid(Grid *grid, int size)
{
	int i;

	grid->size = size;
	grid->region_size = sqrt(size);
	grid->grid = calloc(size, sizeof(char*));

	for(i = 0; i < size; i++)
		grid->grid[i] = calloc(size, sizeof(char));
}

void destroy_grid(Grid *grid)
{
	int i;
	for(i = 0; i < grid->size; i++)
		free(grid->grid[i]);
	free(grid->grid);
}

int format_ok(char *buffer, size_t len)
{
	size_t i;
	for(i = 0; i < len; i++)
	{
		if(!AUTHORIZED_CHAR(buffer[i], (int)len))
			return 0;
	}

	return 1;
}

int load_grid(FILE *stream, Grid *grid)
{
	char *buffer = NULL;
	size_t len;
	int i;
	
	buffer = fgetln(stream, &len);
	
	if(buffer == NULL)
		return BAD_STREAM;
	
	if(((len-1) < _MIN_) || ((len-1) > _MAX_) || 
		!format_ok(buffer, len-1))
		return BAD_FORMAT;
	
	create_grid(grid, len-1);
	strncpy(grid->grid[0], buffer, grid->size);

	for(i = 1; i < grid->size; i++)
	{
		buffer = fgetln(stream, &len);

		if((buffer == NULL) || (len < (unsigned int)grid->size) || 
			!format_ok(buffer, grid->size))
		{
			destroy_grid(grid);
			return BAD_FORMAT;
		}

		strncpy(grid->grid[i], buffer, grid->size);
	}

	return SUCCESS;
}

int load_from_file(char *file, Grid *grid)
{
	FILE *stream = fopen(file, "r");
	int code;

	if(stream == NULL)
		return BAD_STREAM;
	
	code = load_grid(stream, grid);
	fclose(stream);

	return code;
}

void print_grid(Grid *grid)
{
	int i, j;
	for(i = 0; i < grid->size; i++)
	{
		for(j = 0; j < grid->size; j++)
			putchar(grid->grid[i][j]);
		putchar('\n');
	}
}
