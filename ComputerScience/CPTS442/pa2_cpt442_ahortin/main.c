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
//50 100 150
static float angle=0.0,ratio;
static float x=0.0f,y=.5f,z=0.0f;
static float lx=0.0f,ly=-.0f,lz=0.f;
static GLint boxDisplayList;
char  Maze[33][32];
int loltest = 0;
int tempmousex = 0,tempmousey=0;
int frustrum = 100;
int w2 =640,h2=360;
void changeSize(int w, int h)
{
	printf("%d",frustrum);
	if(h == 0)
		h = 1;
	w2 = w;
	h2 = h;
	ratio = 1.0f * w / h;
	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);

	// Set the clipping volume
	gluPerspective(frustrum,ratio,.1,1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(x, y, z, 
		      x + lx,y + ly,z + lz,
			  0.0f,1.0f,0.0f);
	//redraw();
}


void drawCube(void) {

	glTranslatef(0.0f ,.5f, 0.0f);
	
	glutSolidCube(0.999f);
	glColor3f(.0f, .0f, .0f);
	glutWireCube(1.0f);
}



GLuint create_display_list() {
	GLuint boxDL;
    boxDL = glGenLists(1);
	// start list
	glNewList(boxDL,GL_COMPILE);
		drawCube();//contains all rendering commands
	glEndList();
	return(boxDL);
}

void initScene() {

	glEnable(GL_DEPTH_TEST);
	boxDisplayList = create_display_list();

}





void redraw(void) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	// Set the viewport to be the entire window
    glViewport(0, 0, w2, h2);

	// Set the clipping volume
	gluPerspective(frustrum,ratio,.1,1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(x, y, z, 
		      x + lx,y + ly,z + lz,
			  0.0f,1.0f,0.0f);
	//redraw();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    int i,j,ivert=32,ihorz=0;
// Draw ground
    glColor3f(.50f, .50f, 1.0f);    
    glutSolidCube(200.0f);
	//printf("redraw\n");
	glColor3f(0.9f, 0.9f, 0.9f);
	glBegin(GL_QUADS);
		glVertex3f(-160.0f, -1.0f, -160.0f);
		glVertex3f(-160.0f, -1.0f,  160.0f);
		glVertex3f( 160.0f, -1.0f,  160.0f);
		glVertex3f( 160.0f, -1.0f, -160.0f);
	glEnd();
	
	for(i=0; i < ivert-1;i++){
        while (Maze[ihorz][i] != '\0'){
            //if (Maze[ihorz][i] == ' ' ||Maze[ihorz][i] == 'x'  ||Maze[ihorz][i] == '*'){
            //}
            if (Maze[ihorz][i] != 'r' && Maze[ihorz][i] != 'g'  &&Maze[ihorz][i] != 'b' &&
                Maze[ihorz][i] != 'c' && Maze[ihorz][i] != 'm'  &&Maze[ihorz][i] != 'y')  {
            }
            
            else{                	
                switch (Maze[ihorz][i]) {
		        case 'r' : glColor3f(1.0f, 0.0f, 0.0f);break;
        		case 'g' : glColor3f(0.0f, 1.0f, 0.0f);break;
        		case 'b' : glColor3f(0.0f, 0.0f, 1.0f);break;
        		case 'c' : glColor3f(0.0f, 1.0f, 1.0f);break;
        		case 'm' : glColor3f(1.0f, 0.0f, 1.0f);break;
        		case 'y' : glColor3f(1.0f, 1.0f, 0.0f);break;
	            }
				
                glPushMatrix();
    			glTranslatef(i*1,0,ihorz*1 );
                if (loltest ==0)            
                    printf("i: %d, ihorz: %d, color %c\n", i, ihorz, Maze[ihorz][i]);
                
                glCallList(boxDisplayList);;
    			glPopMatrix();
				
				
			}            
            ihorz++;    
        
        }
        ihorz = 0;
        
    }      
	loltest = 1;
            
	glutSwapBuffers();
}

void orientMe(float ang) {
	int i = 0,tempx,tempy;
	//ang = ang/10;
	//tempx = lx - sin(ang
	//tempy = lz - (-cos(ang));
		
	printf("(lx: %lf, lz: %lf)",lx,lz);
	//for (i=0;i>0;i--)
	//{
		lx = sin(ang);
		lz = -cos(ang);
	     //usleep(36000);
         glLoadIdentity();
	        gluLookAt(x, y, z, 
		          x + lx,y + ly,z + lz,
			      0.0f,1.f,0.0f);      
          redraw();   
	//}
}
void orients(int lol)
{
	int i =0;
	for(i = 0;i<4;i++){
		angle += ((3.14159/8) * lol);
		usleep(100000);
		orientMe(angle);
	}
}
void mousemove(int x,int y)
{
    if ((tempmousex - x) > 20)    
    {
          angle -= (3.14159/16);
            orientMe(angle);
            tempmousex = x;
    }
    else if ((tempmousex - x) < -20)
    {
     angle += (3.14159/16);
            orientMe(angle);
            tempmousex = x;
    
    }    
    if ((tempmousey - y) > 20)    
    {
            ly += .1;
            orientMe(angle);
            tempmousey = y;
    }
    else if ((tempmousey - y) < -20)
    {
            ly -= .1;
            orientMe(angle);
            tempmousey = y;
    
    }    
    

}

void moveMeFlat(int i) {
	int i2;    
	//printf(" rounded z: %d, x %d,c %c\n",(int)round((z + i*(lz))),(int)(round((x + i*(lx)))),Maze[(int)round((z + i*(lz)))][(int)(round((x + i*(lx))))]);
    if (Maze[(int)round((z + i*(lz)))][(int)(round((x + i*(lx))))] == ' ' || Maze[(int)round((z + i*(lz)))][(int)(round((x + i*(lx))))] == '*' ) 	
    {
        for (i2=0;i2<4;i2++){
        x += i*(lx)/4;
	    z += i*(lz)/4;
		usleep(100000);
	    //printf("(%lf, %lf)\n",x,z);
	    glLoadIdentity();
	    gluLookAt(x, y, z, 
		          x + lx,y + ly,z + lz,
			      0.0f,1.f,0.0f);
		redraw();
		}
    }
    if (Maze[(int)round((z + i*(lz)))][(int)(round((x + i*(lx))))] == 'x')
    {
        printf("You Win!\n");
        exit(1);
    }
}
void jump(void){
    
    while( y < 3 )
      {
         y += .25;
         usleep(36000);
         glLoadIdentity();
	        gluLookAt(x, y, z, 
		          x + lx,y + ly,z + lz,
			      0.0f,1.f,0.0f);      
          redraw();     
      }
      usleep(500);  //small jump linger
          
     while( y  > .5 )
      {
        
         y -= .25;
         usleep(36000);
        glLoadIdentity();
	        gluLookAt(x, y, z, 
		          x + lx,y + ly,z + lz,
			      0.0f,1.f,0.0f);      
          redraw();     
      }
    
	
}
void changefrust(void)
{
	if (frustrum == 100){
		frustrum = 50;
	}
	else if (frustrum == 50){
		frustrum = 150;
	}
	else if (frustrum == 150){
		frustrum = 100;
	}
	changeSize(w2,h2);
}
void inputKey(int key, int x, int y) {
	//set look at later in main
    printf("%d\n", key);
	switch (key) {
		case GLUT_KEY_LEFT : orients(-1);break;
		case GLUT_KEY_RIGHT : orients(1);break;
		case GLUT_KEY_UP : moveMeFlat(1);break;
        case 119:moveMeFlat(1);break;		
        case GLUT_KEY_DOWN : moveMeFlat(-1);break;
        case 115:moveMeFlat(-1);break;
		case 32: jump();break;
        case 106: jump();break;	
		case 118: changefrust();break;	
	}
	glutPostRedisplay();
}
void idle()
{
	glutPostRedisplay();
}
int main (int argc,char *argv[]){
    FILE* fp;
    int ivert=0,ihorz=0,i=0;    
    char tc;    
    static int useDbuf = 1;      /* default: double buffering */
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
			if (Maze[ihorz][i] == '*'){
				z = (ihorz);
				x = (i);	
			}            
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

    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(w2,h2);
	glutCreateWindow("Maze");

	initScene();
	
    
    //glutMotionFunc(mousemove);
	glutSpecialFunc(inputKey);
    glutKeyboardFunc(inputKey);
	glutDisplayFunc(redraw);
	glutIdleFunc(idle);
	
	glutReshapeFunc(changeSize);
	//redraw();
	orients(-1);
	orients(-1);
	glutMainLoop();
    

}







































