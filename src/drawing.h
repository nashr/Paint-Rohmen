#include "canvas.h"

#ifndef DRAWING_H
#define DRAWING_H

#define MAX_LINE 100

// Drawing's global variables
extern rohmen_line lines[ MAX_LINE ];
extern int n_line;

void drawing_translate( int px, int py );

void drawing_rotate( int px, int py );

void drawing_rotate_point( int* x, int* y );

void drawing_rotation_calibrate( int* x, int* y, int r );

void drawing_scale( int cx, int cy, float scale );

void drawing_draw( void );

int drawing_prepare_line( int x, int y );

int drawing_process_line( int x, int y );

int drawing_finalize_line( int x, int y );

#endif