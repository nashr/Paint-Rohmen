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
