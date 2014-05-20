#include "drawing.h"
#include <math.h>
#include <stdio.h>

rohmen_line lines[ MAX_LINE ];
rohmen_polygon polygons;
int n_line; 

// Drawing's global variables
int drawing_ox = -1, drawing_oy = -1;
rohmen_line olines[ MAX_LINE ];

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
	if ( drawing_ox == -1 ) {
		drawing_ox = 999;
		
		int i;
		for ( i = 0; i < n_line; i++ ) {
			olines[ i ] = lines[ i ];
		}
	} else if ( px == 999 ) {
		int i;
		for ( i = 0; i < n_line; i++ ) {
			double r;

			r = sqrt( ( olines[ i ].x0 - rx ) * ( olines[ i ].x0 - rx ) + ( olines[ i ].y0 - ry ) * ( olines[ i ].y0 - ry ) );
			drawing_rotation_calibrate( &lines[ i ].x0, &lines[ i ].y0, r );

			r = sqrt( ( olines[ i ].x1 - rx ) * ( olines[ i ].x1 - rx ) + ( olines[ i ].y1 - ry ) * ( olines[ i ].y1 - ry ) );
			drawing_rotation_calibrate( &lines[ i ].x1, &lines[ i ].y1, r );
		}

		drawing_ox = -1;
		drawing_oy = -1;
	} else {
		int i;
		for ( i = 0; i < n_line; i++ ) {
			lines[ i ] = olines[ i ];

			drawing_rotate_point( &lines[ i ].x0, &lines[ i ].y0 );
			drawing_rotate_point( &lines[ i ].x1, &lines[ i ].y1 );
		}
	}

	return;
}

void drawing_rotate_point( int* x, int* y ) {
	double s = sin( angle * PI / 180 );
	double c = cos( angle * PI / 180 );

	*x -= rx;
	*y -= ry;
	
	int tx = *x;
	int ty = *y;

	*x = tx * c - ty * s;
	*y = tx * s + ty * c;

	*x += rx;
	*y += ry;

	return;
}

void drawing_rotation_calibrate( int* x, int* y, int r ) {
	*x -= rx;
	*y -= ry;

	if ( fabs( *x ) > fabs( *y ) && ( *x ) > 0 ) {
		*x = sqrt( r * r - ( *y ) * ( *y ) ) + 0.5;
	} else if ( fabs( *x ) < fabs( *y ) && ( *y ) > 0 ) {
		*y = sqrt( r * r - ( *x ) * ( *x ) ) + 0.5;
	} else if ( fabs( *x ) > fabs( *y ) && ( *x ) < 0 ) {
		*x = ( -1 ) * ( sqrt( r * r - ( *y ) * ( *y ) ) + 0.5 );
	} else if ( fabs( *x ) < fabs( *y ) && ( *y ) < 0 ) {
		*y = ( -1 ) * ( sqrt( r * r - ( *x ) * ( *x ) ) + 0.5 );
	} else {
		if ( ( *x ) > 0 && ( *y ) < 0 ) {
			*x = sqrt( r * r - ( *y ) * ( *y ) ) + 0.5;
		} else if ( ( *x ) > 0 && ( *y ) > 0 ) {
			*y = sqrt( r * r - ( *x ) * ( *x ) ) + 0.5;
		} else if ( ( *x ) < 0 && ( *y ) > 0 ) {
			*x = ( -1 ) * ( sqrt( r * r - ( *y ) * ( *y ) ) + 0.5 );
		} else if ( ( *x ) < 0 && y < 0 ) {
			*y = ( -1 ) * ( sqrt( r * r - ( *x ) * ( *x ) ) + 0.5 );
		}
	}

	*x += rx;
	*y += ry;

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