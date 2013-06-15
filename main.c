#include <stdio.h>
#include <stdlib.h>
#include "grid.h"

int main(int argc, char **argv)
{
	Grid grid;
	int error;

	if(argc == 1)
		error = load_grid(stdin, &grid);
	else if(argc == 2)
		error = load_from_file(argv[1], &grid);
	else
	{
		fprintf(stderr, "usage: sdksolver [file]\n");
		return 1;
	}

	if(error == BAD_FORMAT)
	{
		fprintf(stderr, "Bad formating\n");
		return 2;
	}
	else if(error == BAD_STREAM)
	{
		fprintf(stderr, "cannot read from %s\n", (argc == 1) ? "stdin" : argv[1]);
		return 3;
	}
	
	print_grid(&grid);

	destroy_grid(&grid);

	return 0;
}
