#include "local.h"

typedef enum { DL_OBJECT = 1 } DisplayList; 

const int winW = 600;
const int winH = 600;

/* vw_init -- initialize the view */
void vw_init(
    char *title, int useDbuf)
{
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(winW, winH);
	glutCreateWindow(title);
    glEnable(GL_DEPTH_TEST);

    glClearColor(0.0, 0.0, 0.4, 1.0);
#ifdef USE_DISPLAY_LIST
    glNewList(DL_OBJECT, GL_COMPILE);
    object_draw();
    glEndList();
#endif
}

static void object_draw(void)
{
    int i, j, k;
    glColor3d(1.0, 1.0, 1.0);
    for (i = 0;i < Shape.numfaces; i++){ 
		glBegin(GL_LINE_LOOP);
        for (j=0;j<Shape.faces[i].vertnums;j++){      
            k = Shape.faces[i].facearray[j];
            glVertex3f(Shape.verts[k].x,Shape.verts[k].y,Shape.verts[k].z);         
             
            
        }        
		glEnd();
    }    
    
    
}

void vw_redraw(void)
{
	GLdouble m[16];
    GLenum err;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    /* 
     * The trackball assumes rotation takes place about the origin, so
     * that's where our view volume must be centered.  Also, zNear and
     * zFar are not coordinates, but distances from the look-at point.
     */
    glOrtho(-1.0,1.0, -1.0,1.0, 0.0,2.0);

	glMatrixMode(GL_MODELVIEW); 
	glLoadIdentity();
    gluLookAt(0.0,0.0,1.0, 0.0,0.0,0.0, 0.0,1.0,0.0);

    qtn_asRotmatrix(qtnCur, m);
    glMultMatrixd(m);

#ifdef USE_DISPLAY_LIST
    glCallList(DL_OBJECT);
#else
    object_draw();
#endif

    err = glGetError();
    if (err != GL_NO_ERROR) {
        fprintf(stderr, "OpenGL error: \"%s\" -- exiting\n",
                gluErrorString(err));
        exit(1);
    }

    glutSwapBuffers();
}
