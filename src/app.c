#include "app.h"
#include "config.h"
#include <stdio.h>

int exit;
rohmen_panel menu_panels[7];
rohmen_panel side_panels[7];

void app_start( void ) {
	exit = false;

	return;
}

void app_handle_input( void ) {
	g_mousestate state;
	getmousestate(&state);

	return;
}

void app_update( void ) {
	return;
}

void app_draw( void ) {
	canvas_begin_draw();
	
	// Draw menu panels
	// 1 - Menu Cartesian
	canvas_draw_rectangle( 0, 0, 64, 32, MENU_BORDER_COLOR_FOCUS, MENU_COLOR_FOCUS );
	
	// 2 - Menu Move
	canvas_draw_rectangle( 64, 0, 160, 32, MENU_BORDER_COLOR, MENU_COLOR );
	
	// 3 - Menu Rotate
	canvas_draw_rectangle( 160, 0, 256, 32, MENU_BORDER_COLOR, MENU_COLOR );
	
	// 4 - Menu Skew
	canvas_draw_rectangle( 256, 0, 352, 32, MENU_BORDER_COLOR, MENU_COLOR );
	
	// 5 - Menu Mirror
	canvas_draw_rectangle( 352, 0, 448, 32, MENU_BORDER_COLOR, MENU_COLOR );
	
	// 6 - Menu Zoom In
	canvas_draw_rectangle( 448, 0, 544, 32, MENU_BORDER_COLOR, MENU_COLOR );
	
	// 7 - Menu Zoom Out
	canvas_draw_rectangle( 544, 0, 640, 32, MENU_BORDER_COLOR, MENU_COLOR );
	
	// Draw side panels
	// 1 - Panel SELECT
	canvas_draw_rectangle( 0, 32, 64, 96, PANEL_BORDER_COLOR_FOCUS, PANEL_COLOR_FOCUS );
	//canvas_draw_line( 10, 54, 54, 10, 0 );
	
	// 2 - Panel LINE
	canvas_draw_rectangle( 0, 96, 64, 160, PANEL_BORDER_COLOR, PANEL_COLOR );
	canvas_draw_line( 10, 150, 54, 106, PANEL_FONT_COLOR );
	
	// 3 - Panel CURVE
	canvas_draw_rectangle( 0, 160, 64, 224, PANEL_BORDER_COLOR, PANEL_COLOR );
	//canvas_draw_line( 10, 54, 54, 10, 0 );
	
	// 4 - Panel ELLIPSE
	canvas_draw_rectangle( 0, 224, 64, 288, PANEL_BORDER_COLOR, PANEL_COLOR );
	//canvas_draw_line( 10, 54, 54, 10, 0 );
	
	// 5 - Panel POLYGON
	canvas_draw_rectangle( 0, 288, 64, 352, PANEL_BORDER_COLOR, PANEL_COLOR );
	//canvas_draw_line( 10, 54, 54, 10, 0 );

	// 6 - Panel FILL
	canvas_draw_rectangle( 0, 352, 64, 416, PANEL_BORDER_COLOR, PANEL_COLOR );
	//canvas_draw_line( 10, 54, 54, 10, 0 );
	
	// 7 - Panel ???
	canvas_draw_rectangle( 0, 416, 64, 480, PANEL_BORDER_COLOR, PANEL_COLOR );
	//canvas_draw_line( 10, 54, 54, 10, 0 );

	canvas_end_draw();

	return;
}

void app_run( void ) {
	canvas_init();

	while ( !app_is_exit() ) {
		app_handle_input();
		app_update();
		app_draw();

		delay( 1000 / 30 );
	}

	canvas_close();

	return;
}

const int app_is_exit( void ) {
	return exit;
}

void app_set_exit( int val ) {
	exit = val;

	return;
}