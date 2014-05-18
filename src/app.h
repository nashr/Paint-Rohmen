#include "canvas.h"

#ifndef APP_H
#define APP_H

typedef struct {
	rohmen_rectangle rect;
	int focus;
} rohmen_panel;

// App's global variables
extern int exit;
extern rohmen_panel menu_panels[7];
extern rohmen_panel side_panels[7];

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