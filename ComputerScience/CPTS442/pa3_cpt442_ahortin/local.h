#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include <unistd.h>
/* for "getopt()" */

#include <assert.h>

#include "trackball.h"
typedef struct vert{
    float x;
    float y;
    float z;
} Vertex;    
typedef struct face{
    int vertnums;
    float * facearray;

    
} Face;    
typedef struct plyshape{
    int numvertexs;
    int numfaces;
    Vertex * verts;
    Face * faces;
	Vertex * normals
}plystruct;
Vertex boundingboxcenter;
plystruct Shape[5];
    
/* in "controller" */
extern Quaternion qtnCur;
extern void ctrl_init(void);

/* in "model" */
enum { N_EDG=6, N_VTX_PER_EDG=2 };
extern double *edg[N_EDG][N_VTX_PER_EDG]; // faces of the cube
extern void mdl_init(char* plyfile,int plyshapenum);

/* in "viewer" */
extern const int winW, winH;
extern void vw_init(char *title, int useDbuf);
extern void vw_redraw(void);
