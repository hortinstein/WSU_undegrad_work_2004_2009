#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include "local.h"

/* this function is provided in the accompanying file */
extern void fillTri(int p[3][2]);

void kbd_hndlr(unsigned char key, int x, int y);
void redraw_hndlr(void);

enum {
    N_CELL_X = 32,
    N_CELL_Y = 32,
    PIXELS_PER_CELL=16 };

static int p[N_VTX][2]; // (x, y) coordinate pairs

/* setCell -- color a particular cell */
void setCell(int x, int y, double r, double g, double b)
{
    if (x < 0 || x >= N_CELL_X) {
        fprintf(stderr, 
                "setCell() called with x = %d outside range [0, %d] -- exiting\n",
                x, N_CELL_X-1);
        exit(EXIT_FAILURE);
    }
    if (y < 0 || y >= N_CELL_Y) {
        fprintf(stderr, 
                "setCell() called with y = %d outside range [0, %d] -- exiting\n",
                y, N_CELL_Y-1);
        exit(EXIT_FAILURE);
    }
    glColor3d(r, g, b);
	glBegin(GL_POLYGON);
	glVertex2d(x, y);
	glVertex2d(x+1, y);
	glVertex2d(x+1, y+1);
	glVertex2d(x, y+1);
	glEnd();
}

/* redraw_hndlr -- redraw the model */
void redraw_hndlr(void)
{
    /* draw a black background */
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

    fillTri(p);

	glFlush();
}

/* kbd_hndlr -- keyboard handler */
void kbd_hndlr(
    unsigned char key,
    int x,
    int y)
{
    switch (key) {

    case '\033':  /* ESC */
    case 'q':
    case 'Q':
        exit(EXIT_SUCCESS);
        break;
    }
}

static void triParse(char **pArg)
{
    int i;

    for (i = 0; i < N_VTX; i++) {
        p[i][0] = atoi(*pArg++);
        p[i][1] = atoi(*pArg++);
    }
    return;
}

int main(
	int argc,
	char *argv[])
{
    int winW = N_CELL_X * PIXELS_PER_CELL;
    int winH = N_CELL_Y * PIXELS_PER_CELL;
    char *progname = argv[0];

	glutInit(&argc, argv);

    if (argc != 1 + 2*N_VTX) {
        fprintf(stderr, "syntax: filltri x0 y0 x1 y1 x2 y2\n");
        exit(EXIT_FAILURE);
    }
    triParse(argv+1);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(winW, winH);
	glutCreateWindow(progname); // window title is program name

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (double) N_CELL_X, 0.0, (double) N_CELL_Y);

	glutDisplayFunc(redraw_hndlr);
    glutKeyboardFunc(kbd_hndlr);
	glutMainLoop();
    exit(EXIT_SUCCESS);  // not reached, but needed to stop gcc complaint
}
