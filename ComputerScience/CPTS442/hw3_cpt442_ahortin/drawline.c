#include <stdio.h>
#include <stdlib.h>
extern void setCell(int x, int y, double r, double g, double b);

/* drawLine -- draw the requested line (works in the 1st octant only!) */
void drawLine(int Ax, int Ay, int Bx, int By)
{
    int yi=Ay,yf=By,xi=Ax,xf=Bx,temp,x,y;
    double delta = 0,ynext = -1,error = 0,dx,dy;
    if ( abs(By-Ay) > abs(Bx-Ax))
    {
        xi = Ay;//making swaps so the algorithm can run a 
        yi = Ax;
        xf = By;
        yf = Bx;
    }
    if (xi > xf)
    {
        temp = xi;//making swaps so the algorithm can run a 
        xi = xf;
        xf = temp;        
        temp = yi;
        yi = yf;
        yf = temp;
    }
    //printf("%d %d %d %d\n", xi, yi, xf, yf);
        
    dy = (abs(yf - yi)) ;
    dx = (xf - xi);
    delta = dy/dx;
    //printf("%lf\n", delta);
        
    if (yi < yf)
    {
        ynext = 1;
    }
    //printf("%d %d %d %d\n", xi, yi, xf, yf);
    //printf("%lf\n", delta);
    
    y = yi;
    for (x = xi; x <= xf; x++) {
        //printf("%d %d %d %d\n", xi, yi, xf, yf);
        if (abs(By-Ay) > abs(Bx-Ax)) 
        {        
            setCell(y, x, 0.4, 0.7, 1.0); 
        }
        else 
        {
            setCell(x, y, 0.4, 0.7, 1.0);
        }
 //       printf("%lf,%lf,%lf\n", y,error,delta);
        
        error+=delta;
        if (error >= .5){
            y+=ynext;
            error--;
        }
    }
}
