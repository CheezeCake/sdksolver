#ifndef SOLVE_H
#define SOLVE_H

#include "grid.h"

#define VERIF(G) (lines(G) && columns(G) && regions(G))

int solve(Grid*, int);
int lines(Grid*);
int columns(Grid*);
int regions(Grid*);

#endif
