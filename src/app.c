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
	
	cartesian.type = TYPE_MENU; cartesian.rect.x0 = 0; cartesian.rect.y0 = 0; cartesian.rect.x1 = 64; cartesian.rect.y1 = 32; cartesian.focus = false;
	move.type = TYPE_MENU; move.rect.x0 = 64; move.rect.y0 = 0; move.rect.x1 = 160; move.rect.y1 = 32; move.focus = false;
	rotate.type = TYPE_MENU; rotate.rect.x0 = 160; rotate.rect.y0 = 0; rotate.rect.x1 = 256; rotate.rect.y1 = 32; rotate.focus = false;
	skew.type = TYPE_MENU; skew.rect.x0 = 256; skew.rect.y0 = 0; skew.rect.x1 = 352; skew.rect.y1 = 32; skew.focus = false;
	mirror.type = TYPE_MENU; mirror.rect.x0 = 352; mirror.rect.y0 = 0; mirror.rect.x1 = 448; mirror.rect.y1 = 32; mirror.focus = false;
	zoom_in.type = TYPE_MENU; zoom_in.rect.x0 = 448; zoom_in.rect.y0 = 0; zoom_in.rect.x1 = 544; zoom_in.rect.y1 = 32; zoom_in.focus = false;
	zoom_out.type = TYPE_MENU; zoom_out.rect.x0 = 544; zoom_out.rect.y0 = 0; zoom_out.rect.x1 = 640; zoom_out.rect.y1 = 32; zoom_out.focus = false;
	
	menu_panels[ 0 ] = cartesian;
	menu_panels[ 1 ] = move;
	menu_panels[ 2 ] = rotate;
	menu_panels[ 3 ] = skew;
	menu_panels[ 4 ] = mirror;
	menu_panels[ 5 ] = zoom_in;
	menu_panels[ 6 ] = zoom_out;

	// Build sidebar panel
	rohmen_panel select, line, curve, ellipse, polygon, fill, empty;
	
	select.type = TYPE_SIDE; select.rect.x0 = 0; select.rect.y0 = 32; select.rect.x1 = 64; select.rect.y1 = 96; select.focus = false;
	line.type = TYPE_SIDE; line.rect.x0 = 0; line.rect.y0 = 96; line.rect.x1 = 64; line.rect.y1 = 160; line.focus = false;
	curve.type = TYPE_SIDE; curve.rect.x0 = 0; curve.rect.y0 = 160; curve.rect.x1 = 64; curve.rect.y1 = 224; curve.focus = false;
	ellipse.type = TYPE_SIDE; ellipse.rect.x0 = 0; ellipse.rect.y0 = 224; ellipse.rect.x1 = 64; ellipse.rect.y1 = 288; ellipse.focus = false;
	polygon.type = TYPE_SIDE; polygon.rect.x0 = 0; polygon.rect.y0 = 288; polygon.rect.x1 = 64; polygon.rect.y1 = 352; polygon.focus = false;
	fill.type = TYPE_SIDE; fill.rect.x0 = 0; fill.rect.y0 = 352; fill.rect.x1 = 64; fill.rect.y1 = 416; fill.focus = false;
	empty.type = TYPE_SIDE; empty.rect.x0 = 0; empty.rect.y0 = 416; empty.rect.x1 = 64; empty.rect.y1 = 480; empty.focus = false;
	
	side_panels[ 0 ] = select;
	side_panels[ 1 ] = line;
	side_panels[ 2 ] = curve;
	side_panels[ 3 ] = ellipse;
	side_panels[ 4 ] = polygon;
	side_panels[ 5 ] = fill;
	side_panels[ 6 ] = empty;
}

void app_draw_panel( rohmen_panel panel ) {
	int border_color, fill_color;

	if ( panel.focus ) {
		if ( panel.type == TYPE_MENU ) {
			border_color = MENU_BORDER_COLOR_FOCUS;
			fill_color = MENU_COLOR_FOCUS;
		} else if ( panel.type == TYPE_SIDE ) {
			border_color = PANEL_BORDER_COLOR_FOCUS;
			fill_color = PANEL_COLOR_FOCUS;
		}
	} else {
		if ( panel.type == TYPE_MENU ) {
			border_color = MENU_BORDER_COLOR;
			fill_color = MENU_COLOR;
		} else if ( panel.type == TYPE_SIDE ) {
			border_color = PANEL_BORDER_COLOR;
			fill_color = PANEL_COLOR;
		}
	}

	canvas_draw_rectangle( panel.rect.x0, panel.rect.y0, panel.rect.x1, panel.rect.y1, border_color, fill_color );
}

void app_handle_input( void ) {
	g_mousestate state;
	getmousestate( &state );

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
		app_draw_panel( menu_panels[ i ] );
	}
	
	// Draw menu icons
	// 1 - CARTESIAN
	if ( menu_panels[ 0 ].focus ) {
		canvas_draw_line( 20, 16, 44, 16, MENU_FONT_COLOR_FOCUS );
		canvas_draw_line( 32, 5, 32, 27, MENU_FONT_COLOR_FOCUS );
		canvas_draw_rectangle( 25, 10, 39, 22, MENU_FONT_COLOR_FOCUS, -1 );
	} else {
		canvas_draw_line( 20, 16, 44, 16, MENU_FONT_COLOR );
		canvas_draw_line( 32, 5, 32, 27, MENU_FONT_COLOR );
		canvas_draw_rectangle( 25, 10, 39, 22, MENU_FONT_COLOR, -1 );
	}
	
	// 2 - MOVE
	
	// 3 - ROTATE
	
	// 4 - SKEW
	
	// 5 - MIRROR
	
	// 6 - ZOOM IN
	
	// 7 - ZOOM OUT

	// Draw side panels
	for ( i = 0; i < 7; i++ ) {
		app_draw_panel( side_panels[ i ] );
	}

	// Draw side icons
	// 1 - SELECT
	
	// 2 - LINE
	if ( side_panels[ 1 ].focus ) {
		canvas_draw_line( 10, 150, 54, 106, PANEL_FONT_COLOR_FOCUS );
	} else {
		canvas_draw_line( 10, 150, 54, 106, PANEL_FONT_COLOR );
	}
	
	// 3 - CURVE
	
	// 4 - ELLIPSE
	
	// 5 - POLYGON
	
	// 6 - FILL
	
	// 7 - EMPTY
	
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