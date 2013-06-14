#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "grid.h"

Grid* create_grid(int size)
{
	Grid *ret = NULL;
	int i;

	ret = malloc(sizeof(Grid));
	ret->size = size;
	ret->region_size = sqrt(size);
	ret->grid = calloc(size, sizeof(char*));

	for(i = 0; i < size; i++)
		ret->grid[i] = calloc(size, sizeof(char));
	
	return ret;
}

void destoy_grid(Grid *grid)
{
	int i;
	for(i = 0; i < grid->size; i++)
		free(grid->grid[i]);
	free(grid->grid);

	free(grid);
}

int format_ok(char *buffer, size_t len)
{
	size_t i;
	for(i = 0; i < (len-1); i++)
	{
		if(!AUTHORIZED_CHAR(buffer[i]))
			return 0;
	}

	return 1;
}

int load_grid(FILE *stream, Grid *grid)
{
	char *buffer = NULL;
	size_t len;
	int i;
	
	grid = NULL;
	buffer = fgetln(stream, &len);
	
	if(buffer == NULL)
		return BAD_STREAM;
	
	if(((len-1) < SIZE_MIN) || ((len-1) > SIZE_MAX))
		return BAD_FORMAT;
	
	if(!format_ok(buffer, len))
		return BAD_FORMAT;
	
	grid = create_grid(len-1);
	strncpy(grid->grid[0], buffer, grid->size);

	for(i = 1; i < grid->size; i++)
	{
		buffer = fgetln(stream, &len);

		if((buffer == NULL) || ((len-1) < (unsigned int)grid->size) || 
			!format_ok(buffer, grid->size))
		{
			destroy_grid(grid);
			grid = NULL;
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
