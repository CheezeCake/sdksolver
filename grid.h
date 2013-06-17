#ifndef GRID_H
#define GRID_H

#include <stdio.h>

#define _MIN_ 2
#define _MAX_ 35

#define IS_NUMBER(X) ((X >= '1') && (X <= '9'))
#define IS_LETTER(X) ((X >= 'A') && (X <= 'Z'))
#define INT(X)  ((IS_NUMBER(X)) ? (X-'0') : ((X-'A')+10))
#define CHAR(X) ((X <= 9) ? (X+'0') : ((X-10)+'A'))

#define AUTHORIZED_CHAR(X, L) ((IS_NUMBER(X) || IS_LETTER(X)) ? (INT(X) <= L) \
                                                              : (X == ' '))

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
