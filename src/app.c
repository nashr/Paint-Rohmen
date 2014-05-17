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
	
	// Draw anything else here
	
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