#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grid.h"
#include "solve.h"

void usage(void);

int main(int argc, char **argv)
{
	Grid grid;
	int error;
	int quiet = 0;

	if(argc == 1)
		error = load_grid(stdin, &grid);
	else if(argc == 2)
	{
		if(strcmp(argv[1], "-q") == 0)
		{
			quiet = 1;
			error = load_grid(stdin, &grid);
		}
		else
			error = load_from_file(argv[1], &grid);
	}
	else if(argc == 3)
	{
		if(strcmp(argv[1], "-q") == 0)
		{
			quiet = 1;
			error = load_from_file(argv[2], &grid);
		}
		else
			usage();
	}
	else
		usage();

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
	else if(!quiet)
		printf("impossible to solve.\n");

	destroy_grid(&grid);

	return 0;
}

void usage(void)
{
	fprintf(stderr, "usage: sdksolver [-q] [file]\n");
	exit(1);
}
