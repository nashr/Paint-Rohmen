#include "canvas.h"

#ifndef DRAWING_H
#define DRAWING_H

#define MAX_LINE 100
#define MAX_POL 10
#define MAX_LINE_POL 50


// Drawing's global variables
extern rohmen_line lines[ MAX_LINE ];
extern rohmen_polygon polygons[ MAX_POL ];
extern int n_line;
extern int n_polygon;

void drawing_translate( int px, int py );

void drawing_rotate( int px, int py );

void drawing_scale( int cx, int cy, float scale );

void drawing_draw( void );

int drawing_prepare_line( int x, int y );

int drawing_process_line( int x, int y );

int drawing_finalize_line( int x, int y );

int drawing_prepare_polygon( int x, int y );

int drawing_process_polygon( int x, int y );

int drawing_finalize_polygon( int x, int y );

#endif