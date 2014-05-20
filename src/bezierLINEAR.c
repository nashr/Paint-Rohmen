#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <math.h>
void bezier (int x[2], int y[2])
{
	int gd = DETECT, gm;
	int i;
	double t;
	initgraph (&gd, &gm, "..\\bgi");
	for (t = 0.0; t < 1.0; t += 0.0005)
	{
		double xt = (1-t) * x[0] + t * x[1];
		double yt = (1-t) * y[0] + t * y[1];  
		putpixel (xt, yt, WHITE);
	}  
	for (i=0; i<2; i++)
		putpixel (x[i], y[i], YELLOW);
		
	getch();
	closegraph();
	return;	
}

void main()
{
	int x[2], y[2];
	int i;  
	printf ("Enter the x- and y-coordinates of the two control points.\n");
	for (i=0; i<2; i++)
		scanf ("%d%d", &x[i], &y[i]);  
	bezier (x, y);
}