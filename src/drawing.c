#include "drawing.h"

int state, count;
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

int drawing_get_line( void ) {
	if ( n_line < MAX_LINE ) {
		if ( state == WAITING ) {
			state = DRAWING_LINE;
			n_line++;
		}
		
		return n_line - 1;
	}

	return -1;
}

void drawing_set_point( int x, int y ) {
	if ( state == DRAWING_LINE ) {
		if ( count == 0 ) {
			lines[ n_line - 1 ].x0 = x;
			lines[ n_line - 1 ].y0 = y;
		} else if ( count == 1 ) {
			lines[ n_line - 1 ].x1 = x;
			lines[ n_line - 1 ].y1 = y;
		}
		count++;
		count %= COUNT_LINE;
		
		if (count == 0) {
			state = WAITING;
		}
	}

	return;
}