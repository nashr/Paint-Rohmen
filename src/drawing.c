#include "drawing.h"
#include <stdio.h>

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

int drawing_prepare_line( int x, int y ) {
	if ( n_line < MAX_LINE && state == WAITING ) {
		state = DRAWING_LINE;

		lines[ n_line ].x0 = x;
		lines[ n_line ].y0 = y;
		
		printf("%d %d", n_line, state);
		
		return true;
	}

	return false;
}

int drawing_process_line( int x, int y ) {
	//printf("%d %d %d %d\n", lines[]);
	if ( x > 64 && y > 32 && state == DRAWING_LINE ) {
		lines[ n_line ].x1 = x;
		lines[ n_line ].y1 = y;
		
		//printf(" %d, %d\n", x, y);
		
		return true;
	}

	return false;
}

int drawing_finalize_line( int x, int y ) {
	if ( x > 64 && y > 32 && state == DRAWING_LINE ) {
		lines[ n_line ].x1 = x;
		lines[ n_line ].y1 = y;
		
		state = WAITING;
		n_line++;
		
		return true;
	}

	return false;
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