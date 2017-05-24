#include "local.h"
#include "stdlib.h"
#include "math.h"
static double xCtr = 0.0;
static double yCtr = 0.0;
static double r = 1.0;
static double n = 6;

static void regpoly_draw(double xCtr, double yCtr, double r, int n);
static void circle_draw(double xCtr, double yCtr, double r);

/* circle_draw -- draw a "effective" circle */
static void circle_draw(double xCtr, double yCtr, double r)
{
    /*
     * To be filled in.
     */
    double theta = 0,s = 0,d = 0,i;//Defining Variables
    
    theta = (360/((double)WH_WINDOW/2))*3.14/180;    

    for (i=0;i<((double)WH_WINDOW/2);i++)
    {
        glVertex2f(xCtr + r*cos(i*theta),yCtr + r*sin(i*theta));    
    }


}

/* mdl_init -- initialize model data structures */
void mdl_init(char *params[])
{
    /*
     * This file will parse the command line arguments contained in
     * "params".
    */
    xCtr = atof(params[0]);
    yCtr = atof(params[1]);
    r = atof(params[2]);
    n = atof(params[3]);
    //printf("Input xCtr: &lf, yCtr: &lf, r: &lf, n: &lf", xCtr,yCtr,r,n);
    
    


}

/* mdl_redraw -- redraw the model */
void mdl_redraw(void)
{
    /*
     * This function is called to draw or redraw the whole contents of
     * the window.  Right now, it draws a square.  Replace this code
     * as directed in the assignment.
     */
    glColor3d(1,0,0);
    glBegin(GL_LINE_LOOP);
        
    regpoly_draw(xCtr,yCtr,r,n);
    glColor3d(0,1,0);

    circle_draw( xCtr, yCtr, r);
    glEnd();
}

/* regpoly_draw -- draw a regular polygon in the current color */
static void regpoly_draw(double xCtr, double yCtr, double r, int n)
{
    /*
     * To be filled in.
     */
    //printf("Input xCtr: &lf, yCtr: &lf, r: &lf, n: &lf", xCtr,yCtr,r,n);
    
    double theta = 0,s = 0,d = 0,i;//Defining Variables
    
    theta = (360/n)*3.14/180;    

    for (i=0;i<n;i++)
    {
        glVertex2f(xCtr + r*cos(i*theta),yCtr + r*sin(i*theta));    
    }

}

