#include "canvas.h"

#ifndef DRAWING_H
#define DRAWING_H

#define MAX_LINE 100
#define MAX_ELLIPSE 30

// Drawing's global variables
extern rohmen_line lines[ MAX_LINE ];
extern rohmen_ellipse ellipses[ MAX_ELLIPSE ];
extern int n_line;
extern int n_ellipse;

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

int drawing_prepare_ellipse( int x, int y );

int drawing_process_ellipse( int x, int y );

int drawing_finalize_ellipse( int x, int y );

#endif