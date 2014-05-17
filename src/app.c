#include "app.h"

int exit;

void app_start( void ) {
	exit = false;

	return;
}

void app_handle_input( void ) {
	return;
}

void app_update( void ) {
	return;
}

void app_draw( void ) {
	canvas_begin_draw();
	
	// Draw panel
	// 1 - Panel garis
	canvas_draw_rectangle( 0, 0, 64, 64, 15, 10 );
	canvas_draw_line( 10, 54, 54, 10, 15 );
	
	canvas_end_draw();

	return;
}

void app_run( void ) {
	canvas_init();

	while ( !app_is_exit() ) {
		app_handle_input();
		app_update();
		app_draw();
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