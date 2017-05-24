#include "local.h"

typedef enum { DL_OBJECT = 1 } DisplayList; 
GLfloat light2[3];
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

    glClearColor(.30, .30, .30, 1.0);
#ifdef USE_DISPLAY_LIST
    glNewList(DL_OBJECT, GL_COMPILE);
    object_draw();
    glEndList();
#endif
}

static void object_draw(void)
{
    int i, j, k,mnum;
	double xmod,ymod,zmod;
    glColor3d(0.2, .20, .20);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   
 
	for(mnum = 0; mnum < 5; mnum++){
		if (mnum == 0){//body
			xmod = 0;
			ymod = 0;
			zmod = 0;
		}
		if (mnum == 1){//right arm
			xmod = (-.35);
			ymod = (.25);
			zmod = (.65);
		}
		if (mnum == 2){//left arm
			xmod = .25;
			ymod = .25;
			zmod = .65;
		}
		if (mnum == 3){//left leg
			printf("newshape\n");		
			xmod = (.15);
			ymod = -1.5;
			zmod = -.2;	
		}
		if (mnum == 4){//right leg
			xmod = (-.15);
			ymod = (-1.5);
			zmod = -.2;
		}
		for (i = 0;i < Shape[mnum].numfaces; i++){ 

		
      
       	
    	glNormal3f(Shape[mnum].normals[i].x,Shape[mnum].normals[i].y,Shape[mnum].normals[i].z);  
        glBegin(GL_POLYGON);
            
         for (j=0;j<Shape[mnum].faces[i].vertnums;j++){      
            k = Shape[mnum].faces[i].facearray[j];
            glVertex3f(Shape[mnum].verts[k].x + xmod,Shape[mnum].verts[k].y+ ymod,Shape[mnum].verts[k].z+zmod);         
        }    
		glEnd();

   
    	}
	}       
}

void vw_redraw(void)
{
	//object_draw();
	GLdouble m[16];
    GLenum err;
    glEnable(GL_RESCALE_NORMAL);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    //glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    glColorMaterial(GL_FRONT,GL_DIFFUSE);
	//Store Light2's position as the first vertex;
	light2[0] = Shape[0].verts[0].x;
	light2[1] = Shape[0].verts[0].y;
	light2[2] = Shape[0].verts[0].z;
	//light1's propeties
    GLfloat ambient[]= { 0.8, 0.2, 0.3, 1.0 } ;                 
    GLfloat diffuse[]= { 0.1, 0.3, 0.1, 1.0 };            
    GLfloat position[]=  { 0.0f, 1.0f, 1.0f, 0.0f };      
    GLfloat specular[] = {0.99, 0.91, 0.81, 1.0};

	//Material
    GLfloat brass_ambient[] = {0.33, 0.22, 0.03, 1.0};
    GLfloat brass_diffuse[] = {0.78, 0.57, 0.11, 1.0};
    GLfloat brass_specular[] = {0.99, 0.91, 0.81, 1.0};
	GLfloat brass_shininess = 7.8;
	//Light2's properties
	GLfloat light_ambient2[]= { 0.0f, 0.9f, 0.0f, 0.1f };
	GLfloat light_diffuse2[]= { 0.0f, 0.9f, 0.0f, 0.0f };
	GLfloat light_specular2[]= { 0.0f, 0.9f, 0.0f, 0.0f };

    
    glMaterialfv(GL_FRONT, GL_AMBIENT, brass_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, brass_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, brass_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, brass_shininess);          


  	glPushMatrix();
	glLoadIdentity();
	glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);
	glPopMatrix(); 
    
	 //glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
        
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
    	glLoadIdentity();
    	glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
		glLightfv(GL_LIGHT1, GL_SPECULAR, specular);
		glLightfv(GL_LIGHT1, GL_POSITION, position);
		glEnable(GL_LIGHT1);
	glPopMatrix();

	//turn on light2
    glLightfv(GL_LIGHT2, GL_AMBIENT, light_ambient2);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, light_diffuse2);
	glLightfv(GL_LIGHT2, GL_SPECULAR, light_specular2);
	glLightfv(GL_LIGHT3, GL_POSITION, light2);
	glEnable(GL_LIGHT2);
	   glColorMaterial ( GL_FRONT_AND_BACK, GL_EMISSION ) ;
   glEnable ( GL_COLOR_MATERIAL ) ;


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glEnable(GL_LIGHT1);

    glOrtho(-3.0,3.0, -3.0,3.0, -3.0,3.0);

	glMatrixMode(GL_MODELVIEW); 
	glLoadIdentity();
    gluLookAt(0.0,0.0,0.2, 0.0,0.0,0.0, 0.0,10.0,0.0);

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
