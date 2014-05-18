#include "app.h"
#include "config.h"
#include <stdio.h>

int exit;
rohmen_panel menu_panels[7];
rohmen_panel side_panels[7];

void app_start( void ) {
	exit = false;
	
	app_build_workspace();

	return;
}

void app_build_workspace( void ) {
	// Build menu
	rohmen_panel cartesian, move, rotate, skew, mirror, zoom_in, zoom_out;
	
	cartesian.rect.x0 = 0; cartesian.rect.y0 = 0; cartesian.rect.x1 = 64; cartesian.rect.y1 = 32; cartesian.focus = false;
	move.rect.x0 = 64; move.rect.y0 = 0; move.rect.x1 = 160; move.rect.y1 = 32; move.focus = false;
	rotate.rect.x0 = 160; rotate.rect.y0 = 0; rotate.rect.x1 = 256; rotate.rect.y1 = 32; rotate.focus = false;
	skew.rect.x0 = 256; skew.rect.y0 = 0; skew.rect.x1 = 352; skew.rect.y1 = 32; skew.focus = false;
	mirror.rect.x0 = 352; mirror.rect.y0 = 0; mirror.rect.x1 = 448; mirror.rect.y1 = 32; mirror.focus = false;
	zoom_in.rect.x0 = 448; zoom_in.rect.y0 = 0; zoom_in.rect.x1 = 544; zoom_in.rect.y1 = 32; zoom_in.focus = false;
	zoom_out.rect.x0 = 544; zoom_out.rect.y0 = 0; zoom_out.rect.x1 = 640; zoom_out.rect.y1 = 32; zoom_out.focus = false;
	
	menu_panels[ 0 ] = cartesian;
	menu_panels[ 1 ] = move;
	menu_panels[ 2 ] = rotate;
	menu_panels[ 3 ] = skew;
	menu_panels[ 4 ] = mirror;
	menu_panels[ 5 ] = zoom_in;
	menu_panels[ 6 ] = zoom_out;

	// Build sidebar panel
}

void app_draw_panel( rohmen_panel panel ) {
	int border_color, fill_color;

	if ( panel.focus ) {
		border_color = MENU_BORDER_COLOR_FOCUS;
		fill_color = MENU_COLOR_FOCUS;
	} else {
		border_color = MENU_BORDER_COLOR;
		fill_color = MENU_COLOR;
	}

	canvas_draw_rectangle( panel.rect.x0, panel.rect.y0, panel.rect.x1, panel.rect.y1, border_color, fill_color );
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
	int i;

	canvas_begin_draw();
	
	// Draw menu panels
	for ( i = 0; i < 7; i++ ) {
		app_draw_panel( menu_panels[i] );
	}
	
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