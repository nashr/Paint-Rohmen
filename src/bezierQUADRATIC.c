#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <math.h>
void bezier (int x[3], int y[3])
{
	int gd = DETECT, gm;
	int i;
	double t;
	initgraph (&gd, &gm, "..\\bgi");
	for (t = 0.0; t < 1.0; t += 0.0005)
	{
		double xt = pow (1-t, 2) * x[0] + 2 * t *(1-t) * x[1] +
					pow (t, 2) * x[2];
		double yt = pow (1-t, 2) * y[0] + 2 * t *(1-t) * y[1] +
					pow (t, 2) * y[2];  
		putpixel (xt, yt, WHITE);
	}  
	for (i=0; i<3; i++)
		putpixel (x[i], y[i], YELLOW);
		
	getch();
	closegraph();
	return;	
}

void main()
{
	int x[3], y[3];
	int i;  
	printf ("Enter the x- and y-coordinates of the three control points.\n");
	for (i=0; i<3; i++)
		scanf ("%d%d", &x[i], &y[i]);  
	bezier (x, y);
}