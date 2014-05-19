#include "drawing.h"
#include <stdio.h>

rohmen_line lines[ MAX_LINE ];
int n_line;

void drawing_scale( int cx, int cy, float scale ) {
	int i;
	
	// Take scale to lines
	for ( i = 0; i < n_line; i++ ) {
		lines[ i ].x0 -= cx;
		lines[ i ].y0 -= cy;
		
		lines[ i ].x0 *= scale;
		lines[ i ].y0 *= scale;
		
		lines[ i ].x0 += cx;
		lines[ i ].y0 += cy;
		
		lines[ i ].x1 -= cx;
		lines[ i ].y1 -= cy;
		
		lines[ i ].x1 *= scale;
		lines[ i ].y1 *= scale;
		
		lines[ i ].x1 += cx;
		lines[ i ].y1 += cy;
	}

	return;
}

void drawing_draw( void ) {
	int i;
	
	// Draw lines
	for ( i = 0; i < n_line; i++ ) {
		canvas_draw_line( lines[ i ].x0, lines[ i ].y0, lines[ i ].x1, lines[ i ].y1, 0 );
	}
	
	return;
}

int drawing_prepare_line( int x, int y ) {
	if ( n_line < MAX_LINE ) {
		n_line++;

		lines[ n_line - 1 ].x0 = x;
		lines[ n_line - 1 ].y0 = y;
		
		lines[ n_line - 1 ].x1 = x;
		lines[ n_line - 1 ].y1 = y;
		
		return true;
	}

	return false;
}

int drawing_process_line( int x, int y ) {
	if ( x > 64 && y > 32 ) {
		lines[ n_line - 1 ].x1 = x;
		lines[ n_line - 1 ].y1 = y;
		
		return true;
	}

	return false;
}

int drawing_finalize_line( int x, int y ) {
	if ( x > 64 && y > 32 ) {
		lines[ n_line - 1 ].x1 = x;
		lines[ n_line - 1 ].y1 = y;

		return true;
	}

	return false;
}