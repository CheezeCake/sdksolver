#include <stdio.h>
#include <stdlib.h>
#include "grid.h"
#include "solve.h"

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
		fprintf(stderr, "bad formating\n");
		return 2;
	}
	else if(error == BAD_STREAM)
	{
		fprintf(stderr, "cannot read from %s\n", (argc == 1) ? "stdin" : argv[1]);
		return 3;
	}
	
	if(solve(&grid, 0))
		print_grid(&grid);
	else
		printf("impossible to solve.\n");

	destroy_grid(&grid);

	return 0;
}
