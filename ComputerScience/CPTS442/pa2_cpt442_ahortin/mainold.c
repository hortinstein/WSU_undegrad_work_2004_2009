//programming assignment 2
//CPTS 442/542
//Nov 2008
//The intent of this assignment is to generate a 3d maze given an ascii input file
//to generate the maze.
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

static float angle=0.0,ratio;
static float x=0.0f,y=1.75f,z=5.0f;
static float lx=0.0f,ly=0.0f,lz=-1.0f;
static GLint snowman_display_list;



void changeSize(int w, int h)
	{

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if(h == 0)
		h = 1;

	ratio = 1.0f * w / h;
	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);

	// Set the clipping volume
	gluPerspective(45,ratio,1,1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(x, y, z, 
		      x + lx,y + ly,z + lz,
			  0.0f,1.0f,0.0f);


	}


void drawSnowMan() {


//	glColor3f(1.0f,0.0f, 0.0f);

// Draw Body	
	glTranslatef(0.0f ,0.75f, 0.0f);
	glutSolidCube(5.5f);


// Draw Head
	glTranslatef(0.0f, 1.0f, 0.0f);
	glutSolidCube(0.5f);

// Draw Nose
	glColor3f(1.0f, 0.5f , 0.5f);
	glRotatef(0.0f,1.0f, 0.0f, 0.0f);
	glutSolidCube(0.5f);
}



GLuint createDL() {
	GLuint snowManDL;

	// Create the id for the list
	snowManDL = glGenLists(1);

	// start list
	glNewList(snowManDL,GL_COMPILE);

	// call the function that contains the rendering commands
		drawSnowMan();

	// endList
	glEndList();

	return(snowManDL);
}

void initScene() {

	glEnable(GL_DEPTH_TEST);
	snowman_display_list = createDL();

}





void redraw(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

// Draw ground
    glColor3f(1.0f, 1.0f, 1.f);    
    glutSolidCube(100.0f);

	glColor3f(0.9f, 0.9f, 0.9f);
	glBegin(GL_QUADS);
		glVertex3f(-16.0f, 0.0f, -16.0f);
		glVertex3f(-16.0f, 0.0f,  16.0f);
		glVertex3f( 16.0f, 0.0f,  16.0f);
		glVertex3f( 16.0f, 0.0f, -16.0f);
	glEnd();

// Draw 36 SnowMen

	for(int i = -3; i < 1; i++)
		for(int j=-3; j < 1; j++) {
            glColor3f(1.0f, 1.0f, 1.f);    
  			
            glPushMatrix();
			glTranslatef(i*10.0,0,j * 10.0);
			glCallList(snowman_display_list);;
			glPopMatrix();
		}
	glutSwapBuffers();
}

void orientMe(float ang) {


	lx = sin(ang);
	lz = -cos(ang);
	glLoadIdentity();
	gluLookAt(x, y, z, 
		      x + lx,y + ly,z + lz,
			  0.0f,1.0f,0.0f);
}


void moveMeFlat(int i) {
	x = x + i*(lx)*0.1;
	z = z + i*(lz)*0.1;
	glLoadIdentity();
	gluLookAt(x, y, z, 
		      x + lx,y + ly,z + lz,
			  0.0f,1.0f,0.0f);
}

void processNormalKeys(unsigned char key, int x, int y) {

	if (key == 27) 
		exit(0);
}


void inputKey(int key, int x, int y) {

	switch (key) {
		case GLUT_KEY_LEFT : angle -= 0.25f;orientMe(angle);break;
		case GLUT_KEY_RIGHT : angle +=0.25f;orientMe(angle);break;
		case GLUT_KEY_UP : moveMeFlat(10);break;
		case GLUT_KEY_DOWN : moveMeFlat(-10);break;
	}
}int main (int argc,char *argv[]){
    FILE* fp;
    int ivert=0,ihorz=0,i=0;    
    char tc;    
    static int useDbuf = 1;      /* default: double buffering */
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(640,360);
	glutCreateWindow("SnowMen from Lighthouse 3D");

	initScene();
	
    if (argc > 1){
        fp = fopen(argv[1],"r");
    }
    else{       
        printf("...please provide an input file\n"); 
        exit(1);
    }
    
    while (!feof(fp)){
        //reading in all data from the dat file
        tc = getc(fp);
        if (tc!='\n')
        {
            Maze[ihorz][ivert] = tc;
            ihorz++;
        }
        else{
            Maze[ihorz][ivert] = '\0';
            ivert++;
            ihorz = 0;
        }
    }
    ihorz =0;
    //printing out read array for debug purposes
    for(i=0; i < ivert;i++){
        while (Maze[ihorz][i] != '\0'){
            if (Maze[ihorz][i] == ' '){
                printf("_");
            }
            else{
            printf("%c",Maze[ihorz][i]);            
            }            
            ihorz++;    
        }
        ihorz = 0;
        printf("\n");
    }      

    glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(inputKey);

	glutDisplayFunc(redraw);
	glutIdleFunc(redraw);

	glutReshapeFunc(changeSize);

	glutMainLoop();
    

}







































