#include "drawing.h"
#include <math.h>
#include <stdio.h>

rohmen_line lines[ MAX_LINE ];
rohmen_ellipse ellipses[ MAX_ELLIPSE ];
rohmen_polygon polygons [ MAX_POL ];
int n_line;
int n_ellipse;
int n_polygon;

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
        
        for ( i = 0; i < n_ellipse; i++ ) {
			ellipses[ i ].x0 += ( px - drawing_ox );
			ellipses[ i ].y0 += ( py - drawing_oy );

			ellipses[ i ].x1 += ( px - drawing_ox );
			ellipses[ i ].y1 += ( py - drawing_oy );
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
	int j;
	
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
	
	// Take scale to polygons
	for ( i = 0; i <= n_polygon; i++ ) {
		for ( j = 0; j <= polygons[i].curr_line; j++) {
			polygons[i].poline[j].x0 -= cx; 
			polygons[i].poline[j].y0 -= cy; 
			polygons[i].poline[j].x0 *= scale; 
			polygons[i].poline[j].y0 *= scale; 
			polygons[i].poline[j].x0 += cx; 
			polygons[i].poline[j].y0 += cy; 
			
			polygons[i].poline[j].x1 -= cx; 
			polygons[i].poline[j].y1 -= cy; 
			polygons[i].poline[j].x1 *= scale; 
			polygons[i].poline[j].y1 *= scale; 
			polygons[i].poline[j].x1 += cx; 
			polygons[i].poline[j].y1 += cy;
		}
	}

	return;
}

void drawing_draw( void ) {
	int i;
	int j;
	
	// Draw lines
	for ( i = 0; i < n_line; i++ ) {
		canvas_draw_line( lines[ i ].x0, lines[ i ].y0, lines[ i ].x1, lines[ i ].y1, 0 );
	}
	
    for (i = 0; i < n_ellipse; i++) {
        canvas_draw_ellipse_mouse( ellipses[ i ].x0, ellipses[ i ].y0, ellipses[ i ].x1, ellipses[ i ].y1, 0);
    }
    
	//Draw polygons
	for ( i = 0; i <= n_polygon; i++ ) {
		for ( j = 0; j <= polygons[i].curr_line; j++) {
			canvas_draw_line( polygons[i].poline[j].x0, polygons[i].poline[j].y0, polygons[i].poline[j].x1, polygons[i].poline[j].y1, 0);
		}
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
	if ( n_polygon < MAX_POL ) {
		if ( polygons[ n_polygon ].finish ) {
			polygons[ n_polygon ].poline[0].x0 = x;  
			polygons[ n_polygon ].poline[0].y0 = y;  //inisialisasi titik awal garis pertama
			                   
			polygons[ n_polygon ].poline[0].x1 = x;
			polygons[ n_polygon ].poline[0].y1 = y;
			                  
			polygons[ n_polygon ].finish = false;
			
			
		}
		else if ( polygons[ n_polygon ].curr_line < MAX_LINE_POL ){ //jumlah sisi poligon tidak lebih
			polygons[ n_polygon ].curr_line++;
			
			int current = polygons[ n_polygon ].curr_line;
			
			//ambil titik akhir dari garis sebelumnya untuk titik awal
			polygons[ n_polygon ].poline[current].x0 = polygons[ n_polygon ].poline[current-1].x1;
			polygons[ n_polygon ].poline[current].y0 = polygons[ n_polygon ].poline[current-1].y1;
			
			polygons[ n_polygon ].poline[current].x1 = x; 
			polygons[ n_polygon ].poline[current].y1 = y;
		}
		else return false;
		
		return true;
	}

	return false;
}

int drawing_process_polygon( int x, int y ) {
	if ( x > 64 && y > 32 ) {
		//curr_line : sisi poligon yang sedang digambar
		polygons[ n_polygon ].poline[polygons[ n_polygon ].curr_line].x1 = x; 
		polygons[ n_polygon ].poline[polygons[ n_polygon ].curr_line].y1 = y;
		
		return true;
	}

	return false;
}

int drawing_finalize_polygon( int x, int y ) {
	if ( x > 64 && y > 32 ) {
		polygons[ n_polygon ].poline[polygons[ n_polygon ].curr_line].x1 = x; 
		polygons[ n_polygon ].poline[polygons[ n_polygon ].curr_line].y1 = y;
		
		int xAwal = polygons[ n_polygon ].poline[0].x0;
		int yAwal = polygons[ n_polygon ].poline[0].y0;
		if ( x == xAwal && y == yAwal || x == xAwal+10 && y == yAwal+10 || x == xAwal+10 && y == yAwal-10 || x == xAwal-10 && y == yAwal+10 || x == xAwal-10 && y == yAwal-10) 
		//x & y sama dengan titik awal poligon
		{
			polygons[ n_polygon ].finish = true;
			n_polygon++;
		} 

		return true;
	}

	return false;
}


int drawing_prepare_ellipse( int x, int y ) {
    if ( n_ellipse < MAX_ELLIPSE ) {
		ellipses[ n_ellipse ].x0 = x;
		ellipses[ n_ellipse ].y0 = y;
		
		ellipses[ n_ellipse ].x1 = x;
		ellipses[ n_ellipse ].y1 = y;
		
        n_ellipse++;
	}

	return false;
}

int drawing_process_ellipse( int x, int y ) {
    if ( x > 64 && y > 32 ) {
		ellipses[ n_ellipse - 1 ].x1 = x;
		ellipses[ n_ellipse - 1 ].y1 = y;
		
		return true;
	}
    
    return false;
}

int drawing_finalize_ellipse( int x, int y ) {
    if ( x > 64 && y > 32 ) {
		ellipses[ n_ellipse - 1 ].x1 = x;
		ellipses[ n_ellipse - 1 ].y1 = y;

		return true;
	}
    
    return false;
}
