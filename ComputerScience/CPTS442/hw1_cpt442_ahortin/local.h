#include <stdlib.h>
#include <stdio.h>
#include "math.h"

#include <GL/gl.h>
#include <GL/glut.h>

enum {
    WH_WINDOW = 400 /* width and height of the OpenGL window */
};

/* in "mdl.h" */
extern void mdl_init(char *params[]);
extern void mdl_redraw(void);
