#include "boolean.h"
#include <graphics.h>

#ifndef CANVAS_H
#define CANVAS_H

#define START_NODE 0
#define END_NODE 1

typedef struct {
	int x0; int y0;
	int x1; int y1;
} rohmen_line;

typedef struct {
	int x0; int y0;
	int x1; int y1;
} rohmen_rectangle;

// Canvas' global variables
extern int page;
extern int drawing;

// Functions and procedures prototype
void canvas_init( void );

void canvas_close( void );

void canvas_begin_draw( void );

void canvas_end_draw( void );

const int canvas_inactive_page( void );

void canvas_draw_cartesian( int absis_color, int cartesian_color );

void canvas_draw_line( int x0, int y0, int x1, int y1, int color );

void canvas_draw_rectangle( int x0, int y0, int x1, int y1, int border_color, int fill_color );

void canvas_fill_rectangle( int x0, int y0, int x1, int y1, int color );

#endif