#include "boolean.h"

#ifndef CANVAS_H
#define CANVAS_H

#define START_NODE 0
#define END_NODE 1

#define OFFSET_X 64
#define OFFSET_Y 32

#define PI 3.14159265
#define DEFAULT_SCALE 64
#define DEFAULT_ZOOM_IN 1.05
#define DEFAULT_ZOOM_OUT 0.95
#define MAX_ZOOM_OUT 32

typedef struct {
	int x;
	int y;
} rohmen_point;

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
extern int width, height;
extern int center_x, center_y;
extern int scale;
extern int rx, ry;

// Functions and procedures prototype
void canvas_init( void );

void canvas_close( void );

void canvas_begin_draw( void );

void canvas_end_draw( void );

const int canvas_inactive_page( void );

int canvas_translate( int px, int py );

int canvas_rotate( int px, int py );

int canvas_zoom_in( int px, int py );

int canvas_zoom_out( int px, int py );

void canvas_draw_rotation_center( void );

void canvas_draw_cartesian( int absis_color, int cartesian_color );

void canvas_draw_line( int x0, int y0, int x1, int y1, int color );

void canvas_draw_rectangle( int x0, int y0, int x1, int y1, int border_color, int fill_color );

void canvas_fill_rectangle( int x0, int y0, int x1, int y1, int color );

#endif