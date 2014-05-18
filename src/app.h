#include "canvas.h"

#ifndef APP_H
#define APP_H

#define TYPE_MENU 0
#define TYPE_SIDE 1
#define NUM_MENU 7
#define NUM_SIDE 7
#define MAX_COUNTER 30

typedef struct {
	int type;
	rohmen_rectangle rect;
	int focus;
} rohmen_panel;

// App's global variables
extern int counter, exit;
extern rohmen_panel menu_panels[ NUM_MENU ];
extern rohmen_panel side_panels[ NUM_SIDE ];
extern int menu_focus, side_focus;

// Functions and procedures prototype
void app_start( void );

void app_build_workspace( void );

void app_draw_panel( rohmen_panel panel );

void app_handle_input( void );

void app_update( void );

void app_draw( void );

void app_run( void );

const int app_is_exit( void );

void app_set_exit( int val );

#endif