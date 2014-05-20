#include "drawing.h"
#include <math.h>
#include <stdio.h>

rohmen_line lines[ MAX_LINE ];
rohmen_polygon polygons;
int n_line; 

// Drawing's global variables
int drawing_ox = -1, drawing_oy = -1;
double drawing_or;

void drawing_translate( int px, int py ) {
	if ( drawing_ox == -1 || px == -1 ) {
		drawing_ox = px;
		drawing_oy = py;
	} else {
		int i;
		for ( i = 0; i < n_line; i++ ) {
			lines[ i ].x0 += ( px - drawing_ox );
			lines[ i ].y0 += ( py - drawing_oy );

			lines[ i ].x1 += ( px - drawing_ox );
			lines[ i ].y1 += ( py - drawing_oy );
		}
		
		drawing_ox = px;
		drawing_oy = py;
	}
	
	return;
}

void drawing_rotate( int px, int py ) {
	if ( drawing_ox == -1 || px == -1 ) {
		drawing_ox = px;
		drawing_oy = py;
		if ( drawing_ox != -1 ) {
			drawing_or = sqrt( ( drawing_ox - rx ) * ( drawing_ox - rx ) + ( drawing_oy - ry ) * ( drawing_oy - ry ) );
		}
	} else {
		double d = sqrt( ( drawing_ox - px ) * ( drawing_ox - px ) + ( drawing_oy - py ) * ( drawing_oy - py ) );
		double angle = d / drawing_or;
		double s = sin( PI / 18 );
		double c = cos( PI / 18 );
		
		int i;
		for ( i = 0; i < n_line; i++ ) {
			lines[ i ].x0 -= rx;
			lines[ i ].y0 -= ry;
			
			int tx = lines[ i ].x0;
			int ty = lines[ i ].y0;

			lines[ i ].x0 = tx * c - ty * s;
			lines[ i ].y0 = tx * s + ty * c;

			lines[ i ].x0 += rx;
			lines[ i ].y0 += ry;

			lines[ i ].x1 -= rx;
			lines[ i ].y1 -= ry;
			
			tx = lines[ i ].x1;
			ty = lines[ i ].y1;

			lines[ i ].x1 = tx * c - ty * s;
			lines[ i ].y1 = tx * s + ty * c;

			lines[ i ].x1 += rx;
			lines[ i ].y1 += ry;
		}
		
		drawing_ox = px;
		drawing_oy = py;
	}

	return;
}

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

int drawing_prepare_polygon( int x, int y ) {
	if ( n_line < MAX_LINE ) {
		n_line++;
		if ( polygons.finish = true ) {
			lines[ n_line - 1 ].x0 = x;
			lines[ n_line - 1 ].y0 = y;
			polygons.x0 = x;
			polygons.y0 = y;
			polygons.finish = false;
		}
		else {
			lines[ n_line - 1 ].x0 = polygons.prevx;
			lines[ n_line - 1 ].y0 = polygons.prevy;
		}
		
		lines[ n_line - 1 ].x1 = x;
		lines[ n_line - 1 ].y1 = y;
		polygons.prevx = x;
		polygons.prevy = y;
		
		return true;
	}

	return false;
}

int drawing_process_polygon( int x, int y ) {
	if ( x > 64 && y > 32 ) {
		lines[ n_line - 1 ].x1 = x;
		lines[ n_line - 1 ].y1 = y;
		return true;
	}

	return false;
}