#include "canvas.h"

#ifndef DRAWING_H
#define DRAWING_H

#define MAX_LINE 100
#define WAITING 0
#define DRAWING_LINE 1
#define DRAWING_CURVE 2
#define DRAWING_ELLIPSE 3
#define DRAWING_POLYGON 4
#define COUNT_LINE 2

// Drawing's global variables
extern int state, count;
extern rohmen_line lines[ MAX_LINE ];
extern int n_line;

void drawing_draw( void );

int drawing_get_line( void );

void drawing_set_point( int x, int y );

#endif