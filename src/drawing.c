#include "drawing.h"
#include <stdio.h>

rohmen_line lines[ MAX_LINE ];
int n_line;

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
		lines[ n_line ].x0 = x;
		lines[ n_line ].y0 = y;
		
		return true;
	}

	return false;
}

int drawing_process_line( int x, int y ) {
	if ( x > 64 && y > 32 ) {
		lines[ n_line ].x1 = x;
		lines[ n_line ].y1 = y;
		
		return true;
	}

	return false;
}

int drawing_finalize_line( int x, int y ) {
	if ( x > 64 && y > 32 ) {
		lines[ n_line ].x1 = x;
		lines[ n_line ].y1 = y;

		n_line++;
		
		return true;
	}

	return false;
}