#include "app.h"
#include "config.h"
#include <stdio.h>

int exit;

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
	
	// Draw menu
	canvas_draw_rectangle( 0, 0, 640, 32, 0, MENU_COLOR );
	
	// Draw panel
	// 1 - Panel SELECT
	canvas_draw_rectangle( 0, 32, 64, 96, 0, PANEL_COLOR_FOCUS );
	//canvas_draw_line( 10, 54, 54, 10, 0 );
	
	// 2 - Panel LINE
	canvas_draw_rectangle( 0, 96, 64, 160, 0, PANEL_COLOR );
	canvas_draw_line( 10, 150, 54, 106, 0 );
	
	// 3 - Panel CURVE
	canvas_draw_rectangle( 0, 160, 64, 224, 0, PANEL_COLOR );
	//canvas_draw_line( 10, 54, 54, 10, 0 );
	
	// 4 - Panel ELLIPSE
	canvas_draw_rectangle( 0, 224, 64, 288, 0, PANEL_COLOR );
	//canvas_draw_line( 10, 54, 54, 10, 0 );
	
	// 5 - Panel POLYGON
	canvas_draw_rectangle( 0, 288, 64, 352, 0, PANEL_COLOR );
	//canvas_draw_line( 10, 54, 54, 10, 0 );

	// 6 - Panel FILL
	canvas_draw_rectangle( 0, 352, 64, 416, 0, PANEL_COLOR );
	//canvas_draw_line( 10, 54, 54, 10, 0 );
	
	// 7 - Panel ???
	canvas_draw_rectangle( 0, 416, 64, 480, 0, PANEL_COLOR );
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