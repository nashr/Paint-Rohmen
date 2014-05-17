#include "boolean.h"
#include <graphics.h>

#ifndef CANVAS_H
#define CANVAS_H

// Canvas' global variables
extern int page;
extern int drawing;

// Functions and procedures prototype
void canvas_init( void );

void canvas_close( void );

void canvas_begin_draw( void );

void canvas_end_draw( void );

const int canvas_inactive_page( void );

void canvas_draw_line( int x0, int y0, int x1, int y1, int color );

void canvas_draw_rectangle( int x0, int y0, int x1, int y1, int border_color, int fill_color );

#endif