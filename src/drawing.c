#include "drawing.h"
#include <math.h>
#include <stdio.h>

rohmen_line lines[ MAX_LINE ];
rohmen_ellipse ellipses[ MAX_ELLIPSE ];
rohmen_curve curves[ MAX_CURVE ];
rohmen_polygon polygons [ MAX_POL ];
int n_line;
int n_ellipse;
int n_curve;
int n_polygon;


// Drawing's global variables
int drawing_ox = -1, drawing_oy = -1;
rohmen_line olines[ MAX_LINE ];
rohmen_polygon opolygons[ MAX_POL ];

void drawing_translate( int px, int py ) {
	if ( drawing_ox == -1 || px == -1 ) {
		drawing_ox = px;
		drawing_oy = py;
	} else {
		int i, j;
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
		
		for ( i = 0; i <= n_polygon; i++ ) {
			for ( j = 0; j <= polygons[i].curr_line; j++ ) {
				polygons[i].poline[j].x0 += ( px - drawing_ox );
				polygons[i].poline[j].y0 += ( py - drawing_oy );
				
				polygons[i].poline[j].x1 += ( px - drawing_ox );
				polygons[i].poline[j].y1 += ( py - drawing_oy );
			}
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
		for ( i = 0; i < n_polygon; i++ ) {
			opolygons[ i ] = polygons[ i ];
		}
		
	} else if ( px == 999 ) {
		int i, j;
		for ( i = 0; i < n_line; i++ ) {
			double r;

			r = sqrt( ( olines[ i ].x0 - rx ) * ( olines[ i ].x0 - rx ) + ( olines[ i ].y0 - ry ) * ( olines[ i ].y0 - ry ) );
			drawing_rotation_calibrate( &lines[ i ].x0, &lines[ i ].y0, r );

			r = sqrt( ( olines[ i ].x1 - rx ) * ( olines[ i ].x1 - rx ) + ( olines[ i ].y1 - ry ) * ( olines[ i ].y1 - ry ) );
			drawing_rotation_calibrate( &lines[ i ].x1, &lines[ i ].y1, r );
		}
		
		for ( i = 0; i <= n_polygon; i++ ) {
			for ( j = 0; j <= opolygons[i].curr_line; j++ ) {
				double r;
				
				r = sqrt( ( opolygons[i].poline[j].x0 - rx ) * ( opolygons[i].poline[j].x0 - rx ) + ( opolygons[i].poline[j].y0 - ry ) * ( opolygons[i].poline[j].y0 - ry ) );
				drawing_rotation_calibrate( &polygons[i].poline[j].x0, &polygons[i].poline[j].y0, r );

				r = sqrt( ( opolygons[i].poline[j].x1 - rx ) * ( opolygons[i].poline[j].x1 - rx ) + ( opolygons[i].poline[j].y1 - ry ) * ( opolygons[i].poline[j].y1 - ry ) );
				drawing_rotation_calibrate( &polygons[i].poline[j].x1, &polygons[i].poline[j].y1, r );
				
			}
		}

		drawing_ox = -1;
		drawing_oy = -1;
	} else {
		int i,j;
		for ( i = 0; i < n_line; i++ ) {
			lines[ i ] = olines[ i ];

			drawing_rotate_point( &lines[ i ].x0, &lines[ i ].y0 );
			drawing_rotate_point( &lines[ i ].x1, &lines[ i ].y1 );
			
		}
		
		for ( i = 0; i <= n_polygon; i++ ) {
			polygons[i] = opolygons[i];
			for ( j = 0; j <= polygons[i].curr_line; j++ ) {
				

				drawing_rotate_point( &polygons[i].poline[j].x0, &polygons[i].poline[j].y0 );
				drawing_rotate_point( &polygons[i].poline[j].x1, &polygons[i].poline[j].y1 );
				
			
			}
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

void drawing_shear( int px, int py ) {
	if ( drawing_ox == -1 ) {
		drawing_ox = 999;
		
		int i;
		for ( i = 0; i < n_line; i++ ) {
			olines[ i ] = lines[ i ];
		}
		for ( i = 0; i < n_polygon; i++ ) {
			opolygons[ i ] = polygons[ i ];
		}
		
	} else if ( px == 999 ) {
		drawing_ox = -1;
		drawing_oy = -1;
	} else {
		int i,j;
		for ( i = 0; i < n_line; i++ ) {
			lines[ i ] = olines[ i ];

			drawing_shear_point( &lines[ i ].x0, &lines[ i ].y0 );
			drawing_shear_point( &lines[ i ].x1, &lines[ i ].y1 );
			
		}
		for ( i = 0; i <= n_polygon; i++ ) {
			polygons[ i ] = opolygons[ i ];
			for ( j = 0; j <= polygons[ i ].curr_line; j++ ) {
				drawing_shear_point( &polygons[i].poline[j].x0, &polygons[i].poline[j].y0 );
				drawing_shear_point( &polygons[i].poline[j].x1, &polygons[i].poline[j].y1 );
			}
		}
	}

	return;
}

void drawing_shear_point( int* x, int* y ) {
	int tx = *x;
	int ty = *y;

	*y -= sy;
	*y += factor_y * ( tx - sx ) / 100;
	*y += sy;

	*x -= sx;
	*x += factor_x * ( ty - sy ) / 100;
	*x += sx;

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
    
	// Take scale to ellipse
	for ( i = 0; i < n_ellipse; i++ ) {
		ellipses[ i ].x0 -= cx;
		ellipses[ i ].y0 -= cy;
		
		ellipses[ i ].x0 *= scale;
		ellipses[ i ].y0 *= scale;
		
		ellipses[ i ].x0 += cx;
		ellipses[ i ].y0 += cy;
		
		ellipses[ i ].x1 -= cx;
		ellipses[ i ].y1 -= cy;
		
		ellipses[ i ].x1 *= scale;
		ellipses[ i ].y1 *= scale;
		
		ellipses[ i ].x1 += cx;
		ellipses[ i ].y1 += cy;
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
		canvas_draw_line( lines[ i ].x0, lines[ i ].y0, lines[ i ].x1, lines[ i ].y1, lines[ i ].color );
	}
	
    // Draw Ellipses
    for (i = 0; i < n_ellipse; i++) {
        canvas_draw_ellipse_mouse( ellipses[ i ].x0, ellipses[ i ].y0, ellipses[ i ].x1, ellipses[ i ].y1, ellipses[ i ].color_border);
    }
    
	// Draw Curve
	for (i = 0; i < n_curve; i++){
		canvas_draw_bezier( curves[i].px, curves[i].py, curves[i].color );

	}
	
	
	//Draw polygons
	for ( i = 0; i <= n_polygon; i++ ) {
		for ( j = 0; j <= polygons[i].curr_line; j++) {
			canvas_draw_line( polygons[i].poline[j].x0, polygons[i].poline[j].y0, polygons[i].poline[j].x1, polygons[i].poline[j].y1, polygons[i].color_border);
		}
	}
	
	return;
}

int drawing_prepare_line( int x, int y, int color ) {
	if ( n_line < MAX_LINE ) {
		n_line++;

		lines[ n_line - 1 ].x0 = x;
		lines[ n_line - 1 ].y0 = y;
		
		lines[ n_line - 1 ].x1 = x;
		lines[ n_line - 1 ].y1 = y;
		
		lines[ n_line - 1 ].color = color;
		
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

int drawing_prepare_curve( int x, int y, int color ) {
	if ( n_curve < MAX_CURVE ) {
		if ( curves[ n_curve ].finish ) {
			curves[ n_curve ].color = color;
			curves[ n_curve ].px[0] = x;  
			curves[ n_curve ].py[0] = y;  //inisialisasi titik awal garis pertama
			                   
			curves[ n_curve ].px[1] = x;
			curves[ n_curve ].py[1] = y;
			curves[ n_curve ].curr_point = 1;                  
			curves[ n_curve ].finish = false;
			
		}
		else if ( curves[ n_curve ].curr_point <4 ){ //titik ada 2
			curves[ n_curve ].curr_point++;
			
			int current = curves[ n_curve ].curr_point;
			
			//ambil titik akhir dari garis sebelumnya untuk titik awal
			curves[ n_curve ].px[current] = x;
			curves[ n_curve ].py[current] = y;
			printf("\n%d %d", curves[ n_curve ].px[current], curves[ n_curve ].py[current]);

		}
		/*
		else if ( curves[ n_curve ].curr_point == 1 ){ //titik ada 2
			curves[ n_curve ].curr_point++;
			
			int current = curves[ n_curve ].curr_point;
			
			//ambil titik akhir dari garis sebelumnya untuk titik awal
			curves[ n_curve ].px[2] = curves[ n_curve ].px[1];
			curves[ n_curve ].py[2] = curves[ n_curve ].py[1];
			
		}
		else if ( curves[ n_curve ].curr_point == 2 ){ //titik ada 2
			curves[ n_curve ].curr_point++;
			
			int current = curves[ n_curve ].curr_point;
			
			//ambil titik akhir dari garis sebelumnya untuk titik awal
			curves[ n_curve ].px[2] = curves[ n_curve ].px[1];
			curves[ n_curve ].py[2] = curves[ n_curve ].py[1];
			
		}
		else if ( curves[ n_curve ].curr_point == 3 ){ //titik ada 3
			curves[ n_curve ].curr_point++;
			
			int current = curves[ n_curve ].curr_point;
			
			//ambil titik akhir dari garis sebelumnya untuk titik awal
			curves[ n_curve ].px[3] = curves[ n_curve ].px[2];
			curves[ n_curve ].py[3] = curves[ n_curve ].py[2];
		}*/
		else return false;
		
		return true;
	}

	return false;
}

int drawing_process_curve( int x, int y ) {
	if ( x > 64 && y > 32 ) {
		curves[ n_curve ].px[curves[ n_curve ].curr_point]= x;
		curves[ n_curve ].py[curves[ n_curve ].curr_point]= y;
		return true;
	}
	
	return false;
}

int drawing_finalize_curve( int x, int y ) {
	if ( x > 64 && y > 32 ) {
		curves[ n_curve ].px[curves[ n_curve ].curr_point]= x;
		curves[ n_curve ].py[curves[ n_curve ].curr_point]= y;
		if (curves[ n_curve ].curr_point == 3) curves[ n_curve ].finish = true;
		return true;
	}
	
	return false;
}

int drawing_prepare_polygon( int x, int y, int color ) {
	if ( n_polygon < MAX_POL ) {
		if ( polygons[ n_polygon ].finish ) {
			polygons[ n_polygon ].color_border = color;
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
		if ( fabs( x - xAwal ) < MARGIN && fabs( y - yAwal) < MARGIN )
		//x & y sama dengan titik awal poligon
		{
			polygons[ n_polygon ].poline[polygons[ n_polygon ].curr_line].x1 = xAwal; 
			polygons[ n_polygon ].poline[polygons[ n_polygon ].curr_line].y1 = yAwal;

			polygons[ n_polygon ].finish = true;
			n_polygon++;
		} 

		return true;
	}

	return false;
}


int drawing_prepare_ellipse( int x, int y, int color ) {
    if ( n_ellipse < MAX_ELLIPSE ) {
		ellipses[ n_ellipse ].color_border = color;

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
