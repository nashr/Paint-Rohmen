#include "app.h"
#include "config.h"
#include "drawing.h"
#include <graphics.h>
#include <stdio.h>

int mouse_prev_state, mouse_prev_x, mouse_prev_y, exit;
rohmen_panel menu_panels[ NUM_MENU ];
rohmen_panel side_panels[ NUM_SIDE ];
int menu_focus = 1, side_focus = 0;
int chosen_color = 0;

void app_start( void ) {
	exit = false;
	
	app_build_workspace();

	return;
}

void app_build_workspace( void ) {
	// Build menu
	rohmen_panel cartesian, move, rotate, skew, zoom_in, zoom_out, pallete;
	
	cartesian.type = TYPE_MENU; cartesian.rect.x0 = 0; cartesian.rect.y0 = 0; cartesian.rect.x1 = 64; cartesian.rect.y1 = 32; cartesian.focus = false;
	move.type = TYPE_MENU; move.rect.x0 = 64; move.rect.y0 = 0; move.rect.x1 = 128; move.rect.y1 = 32; move.focus = false;
	rotate.type = TYPE_MENU; rotate.rect.x0 = 128; rotate.rect.y0 = 0; rotate.rect.x1 = 192; rotate.rect.y1 = 32; rotate.focus = false;
	skew.type = TYPE_MENU; skew.rect.x0 = 192; skew.rect.y0 = 0; skew.rect.x1 = 256; skew.rect.y1 = 32; skew.focus = false;
	zoom_in.type = TYPE_MENU; zoom_in.rect.x0 = 256; zoom_in.rect.y0 = 0; zoom_in.rect.x1 = 320; zoom_in.rect.y1 = 32; zoom_in.focus = false;
	zoom_out.type = TYPE_MENU; zoom_out.rect.x0 = 320; zoom_out.rect.y0 = 0; zoom_out.rect.x1 = 384; zoom_out.rect.y1 = 32; zoom_out.focus = false;
	pallete.type = TYPE_MENU; pallete.rect.x0 = 384; pallete.rect.y0 = 0; pallete.rect.x1 = 640; pallete.rect.y1 = 32; pallete.focus = false;
	
	menu_panels[ 0 ] = cartesian;
	menu_panels[ 1 ] = move;
	menu_panels[ 2 ] = rotate;
	menu_panels[ 3 ] = skew;
	menu_panels[ 4 ] = zoom_in;
	menu_panels[ 5 ] = zoom_out;
	menu_panels[ 6 ] = pallete;

	// Build sidebar panel
	rohmen_panel select, line, curve, ellipse, polygon, fill, crop;
	
	select.type = TYPE_SIDE; select.rect.x0 = 0; select.rect.y0 = 32; select.rect.x1 = 64; select.rect.y1 = 96; select.focus = false;
	line.type = TYPE_SIDE; line.rect.x0 = 0; line.rect.y0 = 96; line.rect.x1 = 64; line.rect.y1 = 160; line.focus = false;
	curve.type = TYPE_SIDE; curve.rect.x0 = 0; curve.rect.y0 = 160; curve.rect.x1 = 64; curve.rect.y1 = 224; curve.focus = false;
	ellipse.type = TYPE_SIDE; ellipse.rect.x0 = 0; ellipse.rect.y0 = 224; ellipse.rect.x1 = 64; ellipse.rect.y1 = 288; ellipse.focus = false;
	polygon.type = TYPE_SIDE; polygon.rect.x0 = 0; polygon.rect.y0 = 288; polygon.rect.x1 = 64; polygon.rect.y1 = 352; polygon.focus = false;
	fill.type = TYPE_SIDE; fill.rect.x0 = 0; fill.rect.y0 = 352; fill.rect.x1 = 64; fill.rect.y1 = 416; fill.focus = false;
	crop.type = TYPE_SIDE; crop.rect.x0 = 0; crop.rect.y0 = 416; crop.rect.x1 = 64; crop.rect.y1 = 480; crop.focus = false;
	
	side_panels[ 0 ] = select;
	side_panels[ 1 ] = line;
	side_panels[ 2 ] = curve;
	side_panels[ 3 ] = ellipse;
	side_panels[ 4 ] = polygon;
	side_panels[ 5 ] = fill;
	side_panels[ 6 ] = crop;
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
	int i;

	g_mousestate state;
	getmousestate( &state );

	if ( state.buttons == 0 && mouse_prev_state == 0 ) { // hover ( no click )
		mouse_prev_state = 0;
		
		mouse_prev_x = state.x;
		mouse_prev_y = state.y;
	} else if ( state.buttons == 1 && mouse_prev_state == 0 ) { // on mouse down ( left clicked )
		int done = false;
		mouse_prev_state = 1;
		
		if ( !done ) {
			for ( i = 0; i < NUM_MENU; i++ ) {
				if ( state.x > menu_panels[ i ].rect.x0 && state.x < menu_panels[ i ].rect.x1 
					&& state.y > menu_panels[ i ].rect.y0 && state.y < menu_panels[ i ].rect.y1 ) {
					if ( i == 0 ) { // Special case for cartesian ( it's independent from others )
						menu_panels[ i ].focus += 1;
						menu_panels[ i ].focus %= 2;
					} else if ( i == 6 ) { // Special case too for color pallete
						for ( i = 0; i < 16; i++ ) {
							if ( i < 8 ) {
								if ( state.x > 384 + 32 * i && state.x < 384 + 32 * ( i + 1 ) && state.y > 0 && state.y < 16 ) {
									chosen_color = i;
									done = true;
								}
							} else {
								if ( state.x > 384 + 32 * ( i - 8 ) && state.x < 384 + 32 * ( i + 1 - 8 ) && state.y > 16 && state.y < 32 ) {
									chosen_color = i;
									done = true;
								}
							}
						}
					} else {
						menu_focus = i;
					}
					
					done = true;
				}
			}
		}
		
		if ( !done ) {
			for ( i = 0; i < NUM_SIDE; i++ ) {
				if ( state.x > side_panels[ i ].rect.x0 && state.x < side_panels[ i ].rect.x1 
					&& state.y > side_panels[ i ].rect.y0 && state.y < side_panels[ i ].rect.y1 ) {
					side_focus = i;
					
					done = true;
				}
			}
		}
		
		if ( !done ) {
			if ( side_focus == 0 ) { // SELECT
				
			} else if ( side_focus == 1 ) { // LINE
				drawing_prepare_line( state.x, state.y, chosen_color );
			} else if ( side_focus == 2 ) { // CURVE
				
			} else if ( side_focus == 3 ) { // ELLIPSE
				drawing_prepare_ellipse( state.x, state.y );
			} else if ( side_focus == 4 ) { // POLYGON
				drawing_prepare_polygon( state.x, state.y );
				
			} else if ( side_focus == 5 ) { // FILL
				
			} else if ( side_focus == 6 ) { // CROP
				
			}
		}
		
		mouse_prev_x = state.x;
		mouse_prev_y = state.y;
	} else if ( state.buttons == 1 && mouse_prev_state == 1 ) { // on mouse move ( left pressed )
		mouse_prev_state = 1;
		
		if ( side_focus == 0 ) { // SELECT
			
		} else if ( side_focus == 1 ) { // LINE
			drawing_process_line( state.x, state.y );
		} else if ( side_focus == 2 ) { // CURVE
			
		} else if ( side_focus == 3 ) { // ELLIPSE
			drawing_process_ellipse( state.x, state.y );
		} else if ( side_focus == 4 ) { // POLYGON
			drawing_process_polygon( state.x, state.y );
			
		} else if ( side_focus == 5 ) { // FILL
			
		} else if ( side_focus == 6 ) { // CROP
			
		}
		
		mouse_prev_x = state.x;
		mouse_prev_y = state.y;
	} else if ( state.buttons == 0 && mouse_prev_state == 1 ) { // on mouse up ( left released )
		mouse_prev_state = 0;
		
		if ( side_focus == 0 ) { // SELECT
			
		} else if ( side_focus == 1 ) { // LINE
			drawing_finalize_line( state.x, state.y );
		} else if ( side_focus == 2 ) { // CURVE
			
		} else if ( side_focus == 3 ) { // ELLIPSE
			drawing_finalize_ellipse( state.x, state.y );
		} else if ( side_focus == 4 ) { // POLYGON
			drawing_finalize_polygon( state.x, state.y );
			
		} else if ( side_focus == 5 ) { // FILL
			
		} else if ( side_focus == 6 ) { // CROP
			
		}
		
		mouse_prev_x = state.x;
		mouse_prev_y = state.y;
	} else if ( state.buttons == 2 && mouse_prev_state == 0 ) { // on mouse down ( right clicked )
		int done = false;
		mouse_prev_state = 2;

		if ( !done ) {
			if ( menu_focus == 1 ) { // MOVE
				if ( canvas_translate( state.x, state.y ) ) {
					drawing_translate( state.x, state.y );
				}
			} else if ( menu_focus == 2 ) { // ROTATE
				if ( !canvas_change_rotation_center( state.x, state.y ) ) {
					if ( canvas_rotate( state.x - mouse_prev_x, state.y - mouse_prev_y ) ) {
						drawing_rotate( state.x - mouse_prev_x, state.y - mouse_prev_y );
					}	
				}
			} else if ( menu_focus == 3 ) { // SKEW
				// do nothing
			} else if ( menu_focus == 4 ) { // ZOOM IN
				// do nothing
			} else if ( menu_focus == 5 ) { // ZOOM OUT
				// do nothing
			}
		}
		
		mouse_prev_x = state.x;
		mouse_prev_y = state.y;
	} else if ( state.buttons == 2 && mouse_prev_state == 2 ) { // on mouse move ( right pressed )
		mouse_prev_state = 2;

		if ( menu_focus == 1 ) { // MOVE
			if ( canvas_translate( state.x, state.y ) ) {
				drawing_translate( state.x, state.y );
			}
		} else if ( menu_focus == 2 ) { // ROTATE
			if ( !canvas_change_rotation_center( state.x, state.y ) ) {
				if ( canvas_rotate( state.x - mouse_prev_x, state.y - mouse_prev_y ) ) {
					drawing_rotate( state.x - mouse_prev_x, state.y - mouse_prev_y );
				}	
			}
		} else if ( menu_focus == 3 ) { // SKEW
			int dx = state.x - mouse_prev_x;
			int dy = state.y - mouse_prev_y;
			if ( dx < dy ) {
				if ( canvas_shear( 0, dy ) ) {
					// TO DO
				}
			} else {
				if ( canvas_shear( dx, 0 ) ) {
					// TO DO
				}
			}
		} else if ( menu_focus == 4 ) { // ZOOM IN
			if ( canvas_zoom_in( state.x, state.y ) ) {
				drawing_scale( state.x, state.y, DEFAULT_ZOOM_IN );
			}
		} else if ( menu_focus == 5 ) { // ZOOM OUT
			if ( canvas_zoom_out( state.x, state.y ) ) {
				drawing_scale( state.x, state.y, DEFAULT_ZOOM_OUT );
			}
		}

		mouse_prev_x = state.x;
		mouse_prev_y = state.y;
	} else if ( state.buttons == 0 && mouse_prev_state == 2 ) { // on mouse up ( right released )
		mouse_prev_state = 0;

		if ( menu_focus == 1 ) { // MOVE
			if ( canvas_translate( -1, -1 ) ) {
				drawing_translate( -1, -1 );
			}
		} else if ( menu_focus == 2 ) { // ROTATE
			if ( !canvas_change_rotation_center( 999, 999 ) ) {
				if ( canvas_rotate( 999, 999 ) ) {
					drawing_rotate( 999, 999 );
				}
			}
		} else if ( menu_focus == 3 ) { // SKEW
			// do nothing
		} else if ( menu_focus == 4 ) { // ZOOM IN
			// do nothing
		} else if ( menu_focus == 5 ) { // ZOOM OUT
			// do nothing
		}

		mouse_prev_x = state.x;
		mouse_prev_y = state.y;
	} else if ( state.buttons == 3 ) { // both click ( not to be confused with double click )
		// do nothing
	}

	return;
}

void app_update( void ) {
	int i;

	// Focus handle
	for ( i = 1; i < NUM_MENU - 1; i++ ) { // i = 0 ( cartesian ) and i = 6 ( color pallete ) are exceptions
		if ( i == menu_focus ) {
			menu_panels[ i ].focus = true;
		} else {
			menu_panels[ i ].focus = false;
		}
	}

	for ( i = 0; i < NUM_SIDE; i++ ) {
		if ( i == side_focus ) {
			side_panels[ i ].focus = true;
		} else {
			side_panels[ i ].focus = false;
		}
	}

	return;
}

void app_draw( void ) {
	int i;

	canvas_begin_draw();
	
	// Draw cartesian if user wants it
	if ( menu_panels[ 0 ].focus ) {
		canvas_draw_cartesian( CARTESIAN_ABSIS_COLOR, CARTESIAN_COLOR );
	}
	
	// Draw drawings
	drawing_draw();
	
	// Draw menu panels
	for ( i = 0; i < NUM_MENU; i++ ) {
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
	if ( menu_panels[ 1 ].focus ) {
		canvas_draw_line( 80, 16, 85, 11, MENU_FONT_COLOR_FOCUS );
		canvas_draw_line( 80, 16, 85, 21, MENU_FONT_COLOR_FOCUS );
		canvas_draw_line( 85, 16, 107, 16, MENU_FONT_COLOR_FOCUS );
		canvas_draw_line( 107, 11, 112, 16, MENU_FONT_COLOR_FOCUS );
		canvas_draw_line( 107, 21, 112, 16, MENU_FONT_COLOR_FOCUS );

		canvas_draw_line( 91, 10, 96, 5, MENU_FONT_COLOR_FOCUS );
		canvas_draw_line( 96, 5, 101, 10, MENU_FONT_COLOR_FOCUS );
		canvas_draw_line( 96, 5, 96, 27, MENU_FONT_COLOR_FOCUS );
		canvas_draw_line( 91, 22, 96, 27, MENU_FONT_COLOR_FOCUS );
		canvas_draw_line( 96, 27, 101, 22, MENU_FONT_COLOR_FOCUS );
	} else {
		canvas_draw_line( 80, 16, 85, 11, MENU_FONT_COLOR );
		canvas_draw_line( 80, 16, 85, 21, MENU_FONT_COLOR );
		canvas_draw_line( 85, 16, 107, 16, MENU_FONT_COLOR );
		canvas_draw_line( 107, 11, 112, 16, MENU_FONT_COLOR );
		canvas_draw_line( 107, 21, 112, 16, MENU_FONT_COLOR );

		canvas_draw_line( 91, 10, 96, 5, MENU_FONT_COLOR );
		canvas_draw_line( 96, 5, 101, 10, MENU_FONT_COLOR );
		canvas_draw_line( 96, 5, 96, 27, MENU_FONT_COLOR );
		canvas_draw_line( 91, 22, 96, 27, MENU_FONT_COLOR );
		canvas_draw_line( 96, 27, 101, 22, MENU_FONT_COLOR );
	}

	// 3 - ROTATE
	if ( menu_panels[ 2 ].focus ) {
		canvas_draw_ellipse( 160, 16, 10, 10, MENU_FONT_COLOR_FOCUS );
		
		canvas_draw_rectangle( 150, 6, 160, 20, MENU_COLOR_FOCUS, MENU_COLOR_FOCUS );
		
		canvas_draw_line( 160, 6, 165, 1, MENU_FONT_COLOR_FOCUS );
		canvas_draw_line( 160, 6, 165, 11, MENU_FONT_COLOR_FOCUS );
	} else {
		canvas_draw_ellipse( 160, 16, 10, 10, MENU_FONT_COLOR );

		canvas_draw_rectangle( 150, 6, 160, 20, MENU_COLOR, MENU_COLOR );

		canvas_draw_line( 160, 6, 165, 1, MENU_FONT_COLOR );
		canvas_draw_line( 160, 6, 165, 11, MENU_FONT_COLOR );
	}

	// 4 - SKEW
	if ( menu_panels[ 3 ].focus ) {
		canvas_draw_line( 237, 3, 242, 8, MENU_FONT_COLOR_FOCUS );
		canvas_draw_line( 220, 8, 242, 8, MENU_FONT_COLOR_FOCUS );

		canvas_draw_line( 220, 12, 207, 27, MENU_FONT_COLOR_FOCUS );
		canvas_draw_line( 207, 27, 229, 27, MENU_FONT_COLOR_FOCUS );
		canvas_draw_line( 229, 27, 242, 12, MENU_FONT_COLOR_FOCUS );
		canvas_draw_line( 242, 12, 220, 12, MENU_FONT_COLOR_FOCUS );
	} else {
		canvas_draw_line( 237, 3, 242, 8, MENU_FONT_COLOR );
		canvas_draw_line( 220, 8, 242, 8, MENU_FONT_COLOR );

		canvas_draw_line( 220, 12, 207, 27, MENU_FONT_COLOR );
		canvas_draw_line( 207, 27, 229, 27, MENU_FONT_COLOR );
		canvas_draw_line( 229, 27, 242, 12, MENU_FONT_COLOR );
		canvas_draw_line( 242, 12, 220, 12, MENU_FONT_COLOR );
	}
	
	// 5 - ZOOM IN
	if ( menu_panels[ 4 ].focus ) {
		canvas_draw_line( 277, 16, 299, 16, MENU_FONT_COLOR_FOCUS );
		canvas_draw_line( 288, 5, 288, 27, MENU_FONT_COLOR_FOCUS );
	} else {
		canvas_draw_line( 277, 16, 299, 16, MENU_FONT_COLOR );
		canvas_draw_line( 288, 5, 288, 27, MENU_FONT_COLOR );
	}

	// 6 - ZOOM OUT
	if ( menu_panels[ 5 ].focus ) {
		canvas_draw_line( 341, 16, 363, 16, MENU_FONT_COLOR_FOCUS );
	} else {
		canvas_draw_line( 341, 16, 363, 16, MENU_FONT_COLOR );
	}

	// 7 - COLOR PALLETE
	for ( i = 0; i < 16; i++ ) {
		if ( i < 8 ) {
			if ( chosen_color == i ) {
				canvas_draw_rectangle( 384 + 32 * i, 1, 384 + 32 * ( i + 1 ), 16, MENU_FONT_COLOR_FOCUS, i );
			} else {
				canvas_draw_rectangle( 384 + 32 * i, 1, 384 + 32 * ( i + 1 ), 16, MENU_FONT_COLOR, i );
			}
		} else {
			if ( chosen_color == i ) {
				canvas_draw_rectangle( 384 + 32 * ( i - 8 ), 16, 384 + 32 * ( i + 1 - 8 ), 31, MENU_FONT_COLOR_FOCUS, i );
			} else {
				canvas_draw_rectangle( 384 + 32 * ( i - 8 ), 16, 384 + 32 * ( i + 1 - 8 ), 31, MENU_FONT_COLOR, i );
			}
		}
		canvas_draw_line( 384, 31, 640, 31, 0 );
	}

	// Draw side panels
	for ( i = 0; i < NUM_SIDE; i++ ) {
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
	if ( side_panels[ 3 ].focus ) {
		canvas_draw_ellipse_mouse( 32, 256, 57, 272, PANEL_FONT_COLOR_FOCUS );
		//canvas_draw_ellipse( 32, 256, 25, 16, PANEL_FONT_COLOR_FOCUS );
	} else {
		canvas_draw_ellipse_mouse( 32, 256, 57, 272, PANEL_FONT_COLOR );
		//canvas_draw_ellipse( 32, 256, 25, 16, PANEL_FONT_COLOR );
	}
    
	// 5 - POLYGON
	if ( side_panels[ 4 ].focus ) {
		canvas_draw_line( 20, 298, 44, 298, PANEL_FONT_COLOR_FOCUS );
		canvas_draw_line( 44, 298, 54, 320, PANEL_FONT_COLOR_FOCUS );
		canvas_draw_line( 54, 320, 44, 342, PANEL_FONT_COLOR_FOCUS );
		canvas_draw_line( 20, 342, 44, 342, PANEL_FONT_COLOR_FOCUS );
		canvas_draw_line( 20, 342, 10, 320, PANEL_FONT_COLOR_FOCUS );
		canvas_draw_line( 10, 320, 20, 298, PANEL_FONT_COLOR_FOCUS );
	} else {
		canvas_draw_line( 44, 298, 54, 320, PANEL_FONT_COLOR );
		canvas_draw_line( 20, 298, 44, 298, PANEL_FONT_COLOR );
		canvas_draw_line( 54, 320, 44, 342, PANEL_FONT_COLOR );
		canvas_draw_line( 20, 342, 44, 342, PANEL_FONT_COLOR );
		canvas_draw_line( 20, 342, 10, 320, PANEL_FONT_COLOR );
		canvas_draw_line( 10, 320, 20, 298, PANEL_FONT_COLOR );
		
	}
	
	// 6 - FILL
	if ( side_panels[ 5 ].focus ) {
		canvas_draw_line( 20, 372, 44, 362, PANEL_FONT_COLOR_FOCUS );
		canvas_draw_line( 20, 392, 44, 382, PANEL_FONT_COLOR_FOCUS );
		canvas_draw_line( 20, 402, 44, 392, PANEL_FONT_COLOR_FOCUS );
		canvas_draw_line( 20, 422, 44, 402, PANEL_FONT_COLOR_FOCUS );
		canvas_draw_line( 20, 372, 20, 422, PANEL_FONT_COLOR_FOCUS );
		canvas_draw_line( 44, 362, 44, 402, PANEL_FONT_COLOR_FOCUS );
		canvas_fill( 21, 403, BLACK);
	} else {
		canvas_draw_line( 20, 372, 44, 362, PANEL_FONT_COLOR );
		canvas_draw_line( 20, 392, 44, 382, PANEL_FONT_COLOR );
		canvas_draw_line( 20, 402, 44, 392, PANEL_FONT_COLOR );
		canvas_draw_line( 20, 422, 44, 402, PANEL_FONT_COLOR );
		canvas_draw_line( 20, 372, 20, 422, PANEL_FONT_COLOR );
		canvas_draw_line( 44, 362, 44, 402, PANEL_FONT_COLOR );
		canvas_fill( 21, 403, BLACK);
	}
	
	
	// 7 - CROP
	
	// Draw rotation center if it's active
	if ( menu_panels[ 2 ].focus ) {
		canvas_draw_rotation_center();
	}
	
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