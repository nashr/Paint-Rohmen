#include "canvas.h"

int page;
int drawing;

void canvas_init( void ) {
	page = 0;
	drawing = false;

	int gd = DETECT, gm = GM_640x480;
	initgraph( &gd, &gm, "" );

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
	setbkcolor( GREEN );

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
	float m = ( y0 - y1 ) / ( x0 - x1 );
	
	if ( x0 > x1 ) {
		int temp = x0;
		x0 = x1;
		x1 = temp;

		temp = x0;
		x0 = x1;
		x1 = temp;
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

	return;
}