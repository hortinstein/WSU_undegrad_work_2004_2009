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

const int winW = 600;
const int winH = 600;
char  Maze[33][32];
static GLint box_display_list;

void maze_box_init(void)
{
    glTranslatef(0.0f ,0.75f, 0.0f);
	glutSolidCube(5.5f); 

} 

GLuint createDL() {
	GLuint boxDL;
	// Create the id for the list
	boxDL = glGenLists(1);
	// start list
	glNewList(boxDL,GL_COMPILE);

	// function that has the rendering commands
		maze_box_init();
	glEndList();

	return(boxDL);
}


void redraw(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    int i=0,ihorz =0,ivert = 32;
// Draw ground
    glColor3f(.50f, .50f, 1.0f);    
    glutSolidCube(100.0f);

	glColor3f(0.9f, 0.9f, 0.9f);
	glBegin(GL_QUADS);
		glVertex3f(-16.0f, 0.0f, -16.0f);
		glVertex3f(-16.0f, 0.0f,  16.0f);
		glVertex3f( 16.0f, 0.0f,  16.0f);
		glVertex3f( 16.0f, 0.0f, -16.0f);
	glEnd();
    
    for(i=0; i < ivert;i++){
        while (Maze[ihorz][i] != '\0'){
            if (Maze[ihorz][i] == ' '){//if there is nothing there
                glColor3f(.10f, .0f, .0f);    
      			
                glPushMatrix();
			    glTranslatef(i+5,0,ivert+5);
			    glCallList(box_display_list);;
			    glPopMatrix();
                }
                else{//if there is a block 
                    glColor3f(.10f, 1.10f, .0f);    
          			
                    glPushMatrix();
			        glTranslatef(i+5,0,ivert+5);
			        glCallList(box_display_list);;
			        glPopMatrix();
                    
                                   
                }            
                ihorz++;    
        }
        ihorz = 0;
        printf("\n");
    }      
    glutSwapBuffers();
}
int main (int argc,char *argv[]){
    FILE* fp;
    int ivert=0,ihorz=0,i=0;    
    char tc;    
    static int useDbuf = 1;      /* default: double buffering */
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(640,360);
	glutCreateWindow("maze");

    box_display_list = createDL();
    glEnable(GL_DEPTH_TEST);
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

   
    glutDisplayFunc(redraw);
	glutIdleFunc(redraw);

	//glutReshapeFunc(changeSize);

	glutMainLoop();

    

}







































