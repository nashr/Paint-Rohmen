#include "canvas.h"

#ifndef APP_H
#define APP_H

#define TYPE_MENU 0
#define TYPE_SIDE 1
#define NUM_MENU 7
#define NUM_SIDE 7

typedef struct {
	int type;
	rohmen_rectangle rect;
	int focus;
} rohmen_panel;

// App's global variables
extern int mouse_prev_state, mouse_prev_x, mouse_prev_y, exit;
extern rohmen_panel menu_panels[ NUM_MENU ];
extern rohmen_panel side_panels[ NUM_SIDE ];
extern int menu_focus, side_focus;
extern int chosen_color;

// Functions and procedures prototype
void app_start( void );

void app_build_workspace( void );

void app_draw_panel( rohmen_panel panel );

void app_handle_input( void );

void app_update( void );

void app_draw( void );

void app_run( void );

/// Gets the exit variable.
/// If the exit variable is set to true, the app will close on the next loop.
const bool app_is_exit();

/// Sets the exit variable.
/// If the exit variable is set to true, the app will close on the next loop.
void app_set_exit( const bool val );

#endif