#include "local.h"

/*
 * H = 3**(-0.5) is half the edge length of a cube that inscribes a
 * unit sphere.  Four corners of that cube form our (therefore)
 * inscribed tetrahedron.
 */
#define H 0.577350
#define N_VTX 4

static double vtx[N_VTX][3] = {
    {  H,  H,  H },
    { -H,  H, -H },
    { -H, -H,  H },
    {  H, -H, -H },
};

/*
 *  fc[i][j] is a pointer to the coordinate (x,y,z) tuple of the jth
 *  vertex on the ith face of the cube.
 */
double *edg[N_EDG][N_VTX_PER_EDG] = {
    { &vtx[0][0], &vtx[1][0] },
    { &vtx[0][0], &vtx[2][0] },
    { &vtx[0][0], &vtx[3][0] },
    { &vtx[1][0], &vtx[2][0] },
    { &vtx[1][0], &vtx[3][0] },
    { &vtx[2][0], &vtx[3][0] },
};

void mdl_init(char * plyfile)
{   /////////////////////////////////////
    //INITIALIZING SHAPE///////COMPLETE//
    /////////////////////////////////////
    FILE* fp;
    char temp[128],tc,nt[128];    
    int i=0,i2,j=0,tv;
    double xmin,xmax,ymin,ymax,zmin,zmax,dx,dy,dz,R_d,k,v,xxx;
  //  Vertex boundingboxcenter;
    printf("...reading plyfile: %s\n", plyfile);
    fp = fopen(plyfile,"r");
    if (fp == NULL)
        return 0;
    fscanf(fp,"%s",&temp);    
    while (strcmp(temp,"end_header") != 0){
        fscanf(fp,"%s",&temp);    
        //printf("%s\n", temp);
        if (strcmp(temp,"element") == 0){
            fscanf(fp,"%s",&temp);    
            if (strcmp(temp,"face") ==0){
                fscanf(fp,"%d",&Shape.numfaces);    
                printf("...found number of face elements: %d\n", Shape.numfaces); 
            }
            else if (strcmp(temp,"vertex")==0){
                fscanf(fp,"%d",&Shape.numvertexs);
                printf("...found number of vertex elements: %d\n", Shape.numvertexs);             
            }    
        }
    }
    //Allocating Data storage space for meh vertexs's's's and faces!
    Shape.faces = malloc(sizeof(Face[Shape.numfaces+5]));
    Shape.verts = malloc(sizeof(Vertex[Shape.numvertexs+5]));
  


/*	tc = getc(fp);
	for (i=0; i<Shape.numvertexs;i++){
		if (tc!='\n'){
	    	while (tc != '\n'){
	        	tc = getc(fp);          				
			}	
			i--;    
		}    
		else{
			fscanf(fp,"%f %f %f",&Shape.verts[i].x,&Shape.verts[i].y,&Shape.verts[i].z);
            printf("...read vertex %d:      %f %f %f\n",i+1,Shape.verts[i].x,Shape.verts[i].y,Shape.verts[i].z);    
		 }            
	    
	}*/
    while (!feof(fp)){
        tc = getc(fp);
        
        if (tc!='\n'){
            while (tc != '\n'){
                tc = getc(fp);          
            }         
        }        
        if (feof(fp))
            break;    
                
        else if (tc == '\n' && i < Shape.numvertexs){
            fscanf(fp,"%f %f %f",&Shape.verts[i].x,&Shape.verts[i].y,&Shape.verts[i].z);
            printf("...read vertex %d:      %f %f %f\n",i+1,Shape.verts[i].x,Shape.verts[i].y,Shape.verts[i].z);             
            i++;         
        }
        else if (tc =='\n' && i>=Shape.numvertexs && i < (Shape.numvertexs + Shape.numfaces)){
            fscanf(fp,"%d",&Shape.faces[i - Shape.numvertexs].vertnums);
            tv = (Shape.faces[i - Shape.numvertexs].vertnums);
            Shape.faces[i - Shape.numvertexs].facearray = malloc(sizeof(int[tv+1]));            
            printf("...read face %d:        %d ",i - Shape.numvertexs,Shape.faces[i - Shape.numvertexs].vertnums);
            for (j=0;j<tv;j++){
                fscanf(fp,"%f",&Shape.faces[i - Shape.numvertexs].facearray[j]);
                printf("%f ", Shape.faces[i - Shape.numvertexs].facearray[j]);
            }
            printf("\n");                            
            i++;  
        }        
        else if (i >= (Shape.numvertexs + Shape.numfaces)){
            break;
        }
    }
    fclose(fp);

	Shape.normals= malloc(sizeof(Vertex[Shape.numfaces+3]));
	for (i=0;i<Shape.numfaces;i++)
	{
		Shape.normals[i].x = 0;
		Shape.normals[i].y = 0;
		Shape.normals[i].z = 0;
	}

	for (i=0;i<Shape.numfaces;i++)
	{
		for (i2=0;i2<Shape.faces[i].vertnums;i2++)
		{
			//printf("vert nums %d",Shape.faces[i].vertnums);
			k = Shape.faces[i].facearray[i2];
			xxx = (i2 + 1) % (int)Shape.faces[i].vertnums;
			v = Shape.faces[i].facearray[(int)xxx];
			Shape.normals[i].x += (Shape.verts[(int)k].y - Shape.verts[(int)v].y) * (Shape.verts[(int)k].z + Shape.verts[(int)v].z);
			Shape.normals[i].y += (Shape.verts[(int)k].z - Shape.verts[(int)v].z) * (Shape.verts[(int)k].x + Shape.verts[(int)v].x);
			Shape.normals[i].z += (Shape.verts[(int)k].x - Shape.verts[(int)v].x) * (Shape.verts[(int)k].y + Shape.verts[(int)v].y);
		}
		//printf("%d %d %d\n",Shape.normals[i].x,Shape.normals[i].y,Shape.normals[i].z);
	}


    /////////////////////////////////////
    //FINDING X,Y,Z Max/Min /////////////
    /////////////////////////////////////    
    xmin = Shape.verts[0].x;
    xmax = Shape.verts[0].x;
    ymin = Shape.verts[0].y;//init all vars to first
    ymax = Shape.verts[0].y;
    zmin = Shape.verts[0].z;
    zmax = Shape.verts[0].z;
    
    for(i=1;i<Shape.numvertexs;i++){
        if (xmin > Shape.verts[i].x){
            xmin = Shape.verts[i].x;
        }
        if (xmax < Shape.verts[i].x){
            xmax = Shape.verts[i].x;
        }
        if (ymin > Shape.verts[i].y){
            ymin = Shape.verts[i].y;
        }
        if (ymax < Shape.verts[i].y){
            ymax = Shape.verts[i].y;
        }
        if (zmin > Shape.verts[i].z){
            zmin = Shape.verts[i].z;
        }
        if (zmax < Shape.verts[i].z){
            zmax = Shape.verts[i].z;
        }
    }
    printf("...xmin: %f, xmax: %f\n", xmin,xmax);
    printf("...ymin: %f, ymax: %f\n", ymin,ymax);
    printf("...zmin: %f, zmax: %f\n", zmin,zmax);
    boundingboxcenter.x = (abs(xmax) - abs(xmin)) * .5;    
    boundingboxcenter.y = (abs(ymax) - abs(ymin)) * .5;
    boundingboxcenter.z = (abs(zmax) - abs(zmin)) * .5;
    printf("...center of bounding box at vertex: (%lf ,%lf ,%lf )\n", boundingboxcenter.x,boundingboxcenter.y, boundingboxcenter.z);
    
    dx = xmax-boundingboxcenter.x;
    dy = ymax-boundingboxcenter.y;
    dz = zmax-boundingboxcenter.z;
    R_d = (float)sqrt( (dx*dx) + (dy*dy) + (dz*dz) ) ;
    printf("...distance is: %f\n",R_d);
    for(i=0;i<Shape.numvertexs;i++){

        Shape.verts[i].x = (float)((Shape.verts[i].x - boundingboxcenter.x)/R_d);     
        Shape.verts[i].y = (float)((Shape.verts[i].y - boundingboxcenter.y)/R_d);
        Shape.verts[i].z = (float)((Shape.verts[i].z - boundingboxcenter.z)/R_d);  
        //intf("...changed vertex %d to:      %f %f %f\n ",i+1,Shape.verts[i].x,Shape.verts[i].y,Shape.verts[i].z);             
                   
    }

}





