#include "canvas.h"
#include "graphics.h"
#include <math.h>
#include <stdio.h>

int page;
int drawing;
int center_x, center_y;
int width, height;
int scale;
int rx, ry, change_r;
double angle;
int sx, sy, change_s;
double factor_x, factor_y;

// Canvas' global variables
int ox = -1, oy = -1;

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
	
	rx = center_x;
	ry = center_y;
	change_r = false;
	
	sx = center_x;
	sy = center_y;
	change_s = false;

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

int canvas_change_rotation_center( int px, int py ) {
	if ( change_r || ( fabs( px - rx ) < 5 && fabs( py - ry ) < 5 ) ) {
		if ( px > OFFSET_X && px < width + OFFSET_X ) {
			rx = px;
		}
		
		if ( py > OFFSET_Y && py < height + OFFSET_Y ) {
			ry = py;
		}

		if ( px == 999 ) {
			change_r = false;
		} else {
			change_r = true;
		}

		return change_r;
	}

	change_r = false;

	return false;
}

int canvas_change_shearing_center( int px, int py ) {
	if ( change_s || ( fabs( px - sx ) < 5 && fabs( py - sy ) < 5 ) ) {
		if ( px > OFFSET_X && px < width + OFFSET_X ) {
			sx = px;
		}
		
		if ( py > OFFSET_Y && py < height + OFFSET_Y ) {
			sy = py;
		}

		if ( px == 999 ) {
			change_s = false;
		} else {
			change_s = true;
		}

		return change_s;
	}

	change_s = false;

	return false;
}

int canvas_translate( int px, int py ) {
	if ( ox == -1 || px == -1 ) {
		ox = px;
		oy = py;
	} else {
		center_x += ( px - ox );
		center_y += ( py - oy );
		
		ox = px;
		oy = py;
	}

	return true;
}

int canvas_rotate( int px, int py ) {
	if ( ox == -1 ) {
		ox = center_x;
		oy = center_y;
		angle = 0;
	} else if ( px == 999 ) {
		double r = sqrt( ( ox - rx ) * ( ox - rx ) + ( oy - ry ) * ( oy - ry ) );

		center_x -= rx;
		center_y -= ry;

		if ( fabs( center_x ) > fabs( center_y ) && center_x > 0 ) {
			center_x = sqrt( r * r - ( center_y ) * ( center_y ) ) + 0.5;
		} else if ( fabs( center_x ) < fabs( center_y ) && center_y > 0 ) {
			center_y = sqrt( r * r - ( center_x ) * ( center_x ) ) + 0.5;
		} else if ( fabs( center_x ) > fabs( center_y ) && center_x < 0 ) {
			center_x = ( -1 ) * ( sqrt( r * r - ( center_y ) * ( center_y ) ) + 0.5 );
		} else if ( fabs( center_x ) < fabs( center_y ) && center_y < 0 ) {
			center_y = ( -1 ) * ( sqrt( r * r - ( center_x ) * ( center_x ) ) + 0.5 );
		} else {
			if ( center_x > 0 && center_y < 0 ) {
				center_x = sqrt( r * r - ( center_y ) * ( center_y ) ) + 0.5;
			} else if ( center_x > 0 && center_y > 0 ) {
				center_y = sqrt( r * r - ( center_x ) * ( center_x ) ) + 0.5;
			} else if ( center_x < 0 && center_y > 0 ) {
				center_x = ( -1 ) * ( sqrt( r * r - ( center_y ) * ( center_y ) ) + 0.5 );
			} else if ( center_x < 0 && center_y < 0 ) {
				center_y = ( -1 ) * ( sqrt( r * r - ( center_x ) * ( center_x ) ) + 0.5 );
			}
		}

		center_x += rx;
		center_y += ry;

		ox = -1;
		oy = -1;
	} else if ( px != 0 || py != 0 ) {
		if ( py < 0 ) {
			angle += py;
			if ( angle < 0 ) {
				angle += 360;
			}
		} else if ( py > 0 ) {
			angle += py;
			if ( angle > 360 ) {
				angle -= 360;
			}
		}

		double s = sin( angle * PI / 180 );
		double c = cos( angle * PI / 180 );
		
		center_x = ox;
		center_y = oy;

		center_x -= rx;
		center_y -= ry;

		int tx = center_x;
		int ty = center_y;

		center_x = tx * c - ty * s + 0.5;
		center_y = tx * s + ty * c + 0.5;

		center_x += rx;
		center_y += ry;
	}

	return true;
}

int canvas_shear( int px, int py ) {
	if ( ox == -1 ) {
		ox = center_x;
		oy = center_y;
		factor_x = 0;
		factor_y = 0;
	} else if ( px == 999 ) {
		ox = -1;
		oy = -1;
	} else if ( px == 0 && py != 0 ) {
		factor_y += py;
		
		center_x = ox;
		center_y = oy;

		center_y -= sy;
		center_y += factor_y * ( center_x - sx ) / 100;
		center_y += sy;
	} else if ( px != 0 && py == 0 ) {
		factor_x += px;

		center_x = ox;
		center_y = oy;

		center_x -= sx;
		center_x += factor_x * ( center_y - sy ) / 100;
		center_x += sx;
	}

	return true;
}

int canvas_zoom_in( int px, int py ) {
	center_x -= px;
	center_y -= py;
	
	center_x *= DEFAULT_ZOOM_IN;
	center_y *= DEFAULT_ZOOM_IN;
	
	scale *= DEFAULT_ZOOM_IN;
	
	center_x += px;
	center_y += py;

	return true;
}

int canvas_zoom_out( int px, int py ) {
	if ( scale > MAX_ZOOM_OUT ) {
		center_x -= px;
		center_y -= py;
		
		center_x *= DEFAULT_ZOOM_OUT;
		center_y *= DEFAULT_ZOOM_OUT;
		
		scale *= DEFAULT_ZOOM_OUT;
		
		center_x += px;
		center_y += py;
		
		return true;
	}

	return false;
}

void canvas_draw_rotation_center( void ) {
	canvas_draw_ellipse( rx, ry, 3, 3, 13 );
	canvas_draw_ellipse( rx, ry, 5, 5, 12 );

	return;
}

void canvas_draw_shearing_center( void ) {
	canvas_draw_line( sx - 5, sy - 5, sx + 5, sy + 5, 13 );
	canvas_draw_line( sx - 5, sy + 5, sx + 5, sy - 5, 13 );

	return;
}

void canvas_draw_cartesian( int absis_color, int cartesian_color ) {
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
	
	canvas_draw_line( 0 + OFFSET_X, center_y, width + OFFSET_X, center_y, absis_color );
	canvas_draw_line( center_x, 0 + OFFSET_Y, center_x, height + OFFSET_Y, absis_color );
	
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

void canvas_ellipsePlotPoints(int xCenter, int yCenter, int x, int y, int color)
{
    putpixel(xCenter + x, yCenter + y, color);
    putpixel(xCenter - x, yCenter + y, color);
    putpixel(xCenter + x, yCenter - y, color);
    putpixel(xCenter - x, yCenter - y, color);
}

void canvas_draw_ellipse_mouse(int xCenter, int yCenter, int x, int y, int color)
{
    // calculate radius
    int Rx = x - xCenter;
    int Ry = y - yCenter;
    if(Rx < 0) Rx = -Rx;
    if(Ry < 0) Ry = -Ry;
    if(Rx > 0 && Ry > 0)
        canvas_draw_ellipse(xCenter, yCenter, Rx, Ry, color);
    
    return;
}

void canvas_draw_ellipse(int xCenter, int yCenter, int Rx, int Ry, int color)
{
    int midx = xCenter;
    int midy = yCenter;

    float p;
    float rxSq = Rx*Rx;
    float rySq = Ry*Ry;
    float rxSq2 = rxSq*2;
    float rySq2 = rySq*2;
    int x = 0, y = Ry;
    float px = 0, py = 2*rxSq*y;

   canvas_ellipsePlotPoints(midx, midy, x, y, color);

    // Region1
    p = rySq - (rxSq*Ry) + (rxSq * 0.25);
    while(px < py) {
        x++;
        px += rySq2;
        if(p < 0) {
            p += rySq + px;
        } else {
            y--;
            py -= rxSq2;
            p += rySq + px - py;
        }
        canvas_ellipsePlotPoints(midx, midy, x, y, color);
    }

    // Region 2
    p = (rySq*(x+0.5)*(x+0.5)) + (rxSq*(y - 1)*(y - 1)) - (rxSq*rySq);

    while(y > 0) {
        y--;
        py -= rxSq2;
        if(p > 0) {
            p += rxSq - py;
        } else {
            x++;
            px += 2*rySq2;
            p += rxSq - py + px;
        }
        canvas_ellipsePlotPoints(midx, midy, x, y, color);
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

void canvas_fill ( int x, int y, int fillColor ) {
	int current;
	current = getpixel ( x, y );
	if (current  !=  fillColor)  {
		setcolor( fillColor );
		putpixel( x, y, 0 );
		canvas_fill( x+1, y, fillColor );
		canvas_fill( x-1, y, fillColor );
		canvas_fill( x,   y+1, fillColor );
		canvas_fill( x,   y-1, fillColor );
	}
}

void canvas_draw_bezier( int length, int* px, int* py, int color ){
	int i;
	double t;
	for (t = 0.0; t < 1.0; t += 0.0005)
	{
		double xt,yt = 0;
		for (i=0; i<legth; i++){
			xt += sp[i] * pow(1-t, length-i) * pow (t,i) * x[i]
			yt += sp[i] * pow(1-t, length-i) * pow (t,i) * y[i]
			m--;
			n++;
			putpixel (xt, yt, WHITE);
		}
	}
	for (i=0; i<3; i++)
		putpixel (x[i], y[i], YELLOW);

	return;	
}