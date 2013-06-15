#ifndef GRID_H
#define GRID_H

#include <stdio.h>

#define SIZE_MIN 1
#define SIZE_MAX 64

#define INT(X)  (X-'0')
#define CHAR(X) (X+'0')

#define AUTHORIZED_CHAR(X) (((X >= '0') && (X <= '9')) || \
                            ((X >= 'A') && (X <= 'Z')) || (X == ' '))

enum {SUCCESS = 0, BAD_FORMAT, BAD_STREAM};

typedef struct grid
{
	char **grid;
	int size;
	int region_size;
} Grid;

void create_grid(Grid*, int size);
void destroy_grid(Grid*);
int load_grid(FILE*, Grid*);
int load_from_file(char*, Grid*);
int format_ok(char*, size_t len);
void print_grid(Grid*);

#endif
