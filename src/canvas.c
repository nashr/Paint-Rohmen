#include "canvas.h"
#include <stdio.h>

int page;
int drawing;
int center_x, center_y;
int width, height;
int scale;

void canvas_init( void ) {
	page = 0;
	drawing = false;

	int gd = DETECT, gm = GM_640x480;
	initgraph( &gd, &gm, "" );

	width = getmaxx() - OFFSET_X;
	height = getmaxy() - OFFSET_Y;

	center_x = width / 2 + OFFSET_X;
	center_y = height / 2 + OFFSET_Y;
	
	scale = DEFAULT_SCALE;

	return;
}

void canvas_close( void ) {
	closegraph();

	return;
}

void canvas_begin_draw( void ) {
	drawing = true;
	setactivepage( canvas_inactive_page() );

	cleardevice();
	setbkcolor(WHITE);

	return;
}

void canvas_end_draw( void ) {
	drawing = false;
	setvisualpage( canvas_inactive_page() );

	page = canvas_inactive_page();

	return;
}

const int canvas_inactive_page( void ) {
	return ( page == 1 ) ? 0 : 1;
}

int canvas_zoom_in( int cx, int cy ) {
	center_x -= cx;
	center_y -= cy;
	
	center_x *= DEFAULT_ZOOM_IN;
	center_y *= DEFAULT_ZOOM_IN;
	
	scale *= DEFAULT_ZOOM_IN;
	
	center_x += cx;
	center_y += cy;

	return true;
}

int canvas_zoom_out( int cx, int cy ) {
	if ( scale > MAX_ZOOM_OUT ) {
		center_x -= cx;
		center_y -= cy;
		
		center_x *= DEFAULT_ZOOM_OUT;
		center_y *= DEFAULT_ZOOM_OUT;
		
		scale *= DEFAULT_ZOOM_OUT;
		
		center_x += cx;
		center_y += cy;
		
		return true;
	}

	return false;
}

void canvas_draw_cartesian( int absis_color, int cartesian_color ) {
	canvas_draw_line( 0 + OFFSET_X, center_y, width + OFFSET_X, center_y, absis_color );
	canvas_draw_line( center_x, 0 + OFFSET_Y, center_x, height + OFFSET_Y, absis_color );
	
	int i;
	for ( i = center_y - scale; i > 0 + OFFSET_Y; i -= scale ) {
		canvas_draw_line( 0 + OFFSET_X, i, width + OFFSET_X, i, cartesian_color );
	}
	
	for ( i = center_y + scale; i < height + OFFSET_Y; i += scale ) {
		canvas_draw_line( 0 + OFFSET_X, i, width + OFFSET_X, i, cartesian_color );
	}
	
	for ( i = center_x - scale; i > 0 + OFFSET_X; i -= scale ) {
		canvas_draw_line( i, 0 + OFFSET_Y, i, height + OFFSET_Y, cartesian_color );
	}
	
	for ( i = center_x + scale; i < width + OFFSET_X; i += scale ) {
		canvas_draw_line( i, 0 + OFFSET_Y, i, height + OFFSET_Y, cartesian_color );
	}
	
	return;
}

void canvas_draw_line( int x0, int y0, int x1, int y1, int color ) {
	int i;

	if ( x0 == x1 ) { // hor
		int start = ( y0 < y1 ) ? y0 : y1;
		int end = ( y0 > y1 ) ? y0 : y1;
		for ( i = start; i <= end; i++ ) {
			putpixel( x0, i, color );
		}
		return;
	}

	if ( y0 == y1 ) { //  ver
		int start = ( x0 < x1 ) ? x0 : x1;
		int end = ( x0 > x1 ) ? x0 : x1;
		for ( i = start; i <= end; i++ ) {
			putpixel(i, y0, color);
		}
		return;
	}

	// mir
	float m = ( y0 - y1 ) * 1.0 / ( x0 - x1 );
	
	if ( m > 1 || m < -1 ) {
		int temp = x0;
		x0 = y0;
		y0 = temp;
		
		temp = x1;
		x1 = y1;
		y1 = temp;
	}
	
	if ( x0 > x1 ) {
		int temp = x0;
		x0 = x1;
		x1 = temp;

		temp = y0;
		y0 = y1;
		y1 = temp;
	}
	
	// inisiasi
	int dx = x1 - x0;
	int dy = y1 - y0;
	
	// inisiasi fungsi parameter
	int p = 2 * dy - dx;
	int c0 = 2 * dy; // konstanta 1
	int c1 = 2 * ( dy - dx ); // konstanta 2
	
	if ( dy < 0 ) {
		p *= -1;
		c0 *= -1;
		c1 = -2 * ( dy + dx );
	}

	// inisiasi pixel
	int x = x0;
	int y = y0;
	
	if ( m > 1 || m < -1 ) {
		putpixel( y, x, color );
	} else {
		putpixel( x, y, color );
	}

	// iterasi pixel
	for ( x = x0 + 1; x <= x1; x++ ) {
		// menentukan nilai p selanjutnya
		if ( p < 0 ) { // nilai y selanjutnya sama dengan y sekarang
			p += c0;
		} else { // nilai y selanjutnya lebih/kurang 1 dari y sekarang
			p += c1;
			if ( dy < 0 ) {
				y--;
			} else {
				y++;
			}
		}
		
		if ( m > 1 || m < -1 ) {
			putpixel( y, x, color );
		} else {
			putpixel( x, y, color );
		}
	}

	return;
}

void canvas_draw_rectangle( int x0, int y0, int x1, int y1, int border_color, int fill_color ) {
	canvas_draw_line( x0, y0, x0, y1, border_color );
	canvas_draw_line( x0, y1, x1, y1, border_color );
	canvas_draw_line( x1, y1, x1, y0, border_color );
	canvas_draw_line( x1, y0, x0, y0, border_color );
	
	if ( fill_color > -1 ) {
		canvas_fill_rectangle( x0, y0, x1, y1, fill_color );
	}

	return;
}

void canvas_fill_rectangle( int x0, int y0, int x1, int y1, int color ) {
	int i, j, inc_i, inc_j;

	if ( x0 < x1 ) {
		inc_i = 1;
	} else {
		inc_i = -1;
	}

	if ( y0 < y1 ) {
		inc_j = 1;
	} else {
		inc_j = -1;
	}

	for ( i = x0 + inc_i; i != x1; i += inc_i ) {
		for ( j = y0 + inc_j; j != y1; j += inc_j ) {
			putpixel( i, j, color );
		}
	}

	return;
}