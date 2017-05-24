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

void mdl_init(char * plyfile,int plyshapenum)
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
                fscanf(fp,"%d",&Shape[plyshapenum].numfaces);    
                printf("...found number of face elements: %d\n", Shape[plyshapenum].numfaces); 
            }
            else if (strcmp(temp,"vertex")==0){
                fscanf(fp,"%d",&Shape[plyshapenum].numvertexs);
                printf("...found number of vertex elements: %d\n", Shape[plyshapenum].numvertexs);             
            }    
        }
    }
    //Allocating Data storage space for meh vertexs's's's and faces!
    Shape[plyshapenum].faces = malloc(sizeof(Face[Shape[plyshapenum].numfaces+5]));
    Shape[plyshapenum].verts = malloc(sizeof(Vertex[Shape[plyshapenum].numvertexs+5]));
  

    while (!feof(fp)){
        tc = getc(fp);
        
        if (tc!='\n'){
            while (tc != '\n'){
                tc = getc(fp);          
            }         
        }        
        if (feof(fp))
            break;    
                
        else if (tc == '\n' && i < Shape[plyshapenum].numvertexs){
            fscanf(fp,"%f %f %f",&Shape[plyshapenum].verts[i].x,&Shape[plyshapenum].verts[i].y,&Shape[plyshapenum].verts[i].z);
            printf("...read vertex %d:      %f %f %f\n",i+1,Shape[plyshapenum].verts[i].x,Shape[plyshapenum].verts[i].y,Shape[plyshapenum].verts[i].z);             
            i++;         
        }
        else if (tc =='\n' && i>=Shape[plyshapenum].numvertexs && i < (Shape[plyshapenum].numvertexs + Shape[plyshapenum].numfaces)){
            fscanf(fp,"%d",&Shape[plyshapenum].faces[i - Shape[plyshapenum].numvertexs].vertnums);
            tv = (Shape[plyshapenum].faces[i - Shape[plyshapenum].numvertexs].vertnums);
            Shape[plyshapenum].faces[i - Shape[plyshapenum].numvertexs].facearray = malloc(sizeof(int[tv+1]));            
            printf("...read face %d:        %d ",i - Shape[plyshapenum].numvertexs,Shape[plyshapenum].faces[i - Shape[plyshapenum].numvertexs].vertnums);
            for (j=0;j<tv;j++){
                fscanf(fp,"%f",&Shape[plyshapenum].faces[i - Shape[plyshapenum].numvertexs].facearray[j]);
                printf("%f ", Shape[plyshapenum].faces[i - Shape[plyshapenum].numvertexs].facearray[j]);
            }
            printf("\n");                            
            i++;  
        }        
        else if (i >= (Shape[plyshapenum].numvertexs + Shape[plyshapenum].numfaces)){
            break;
        }
    }
    fclose(fp);

	Shape[plyshapenum].normals= malloc(sizeof(Vertex[Shape[plyshapenum].numfaces+3]));
	for (i=0;i<Shape[plyshapenum].numfaces;i++)
	{
		Shape[plyshapenum].normals[i].x = 0;
		Shape[plyshapenum].normals[i].y = 0;
		Shape[plyshapenum].normals[i].z = 0;
	}

	for (i=0;i<Shape[plyshapenum].numfaces;i++)
	{
		for (i2=0;i2<Shape[plyshapenum].faces[i].vertnums;i2++)
		{
			//printf("vert nums %d",Shape[plyshapenum].faces[i].vertnums);
			k = Shape[plyshapenum].faces[i].facearray[i2];
			xxx = (i2 + 1) % (int)Shape[plyshapenum].faces[i].vertnums;
			v = Shape[plyshapenum].faces[i].facearray[(int)xxx];
			Shape[plyshapenum].normals[i].x += (Shape[plyshapenum].verts[(int)k].y - Shape[plyshapenum].verts[(int)v].y) * (Shape[plyshapenum].verts[(int)k].z + Shape[plyshapenum].verts[(int)v].z);
			Shape[plyshapenum].normals[i].y += (Shape[plyshapenum].verts[(int)k].z - Shape[plyshapenum].verts[(int)v].z) * (Shape[plyshapenum].verts[(int)k].x + Shape[plyshapenum].verts[(int)v].x);
			Shape[plyshapenum].normals[i].z += (Shape[plyshapenum].verts[(int)k].x - Shape[plyshapenum].verts[(int)v].x) * (Shape[plyshapenum].verts[(int)k].y + Shape[plyshapenum].verts[(int)v].y);
		}
		//printf("%d %d %d\n",Shape[plyshapenum].normals[i].x,Shape[plyshapenum].normals[i].y,Shape[plyshapenum].normals[i].z);
	}


    /////////////////////////////////////
    //FINDING X,Y,Z Max/Min /////////////
    /////////////////////////////////////    
    xmin = Shape[plyshapenum].verts[0].x;
    xmax = Shape[plyshapenum].verts[0].x;
    ymin = Shape[plyshapenum].verts[0].y;//init all vars to first
    ymax = Shape[plyshapenum].verts[0].y;
    zmin = Shape[plyshapenum].verts[0].z;
    zmax = Shape[plyshapenum].verts[0].z;
    
    for(i=1;i<Shape[plyshapenum].numvertexs;i++){
        if (xmin > Shape[plyshapenum].verts[i].x){
            xmin = Shape[plyshapenum].verts[i].x;
        }
        if (xmax < Shape[plyshapenum].verts[i].x){
            xmax = Shape[plyshapenum].verts[i].x;
        }
        if (ymin > Shape[plyshapenum].verts[i].y){
            ymin = Shape[plyshapenum].verts[i].y;
        }
        if (ymax < Shape[plyshapenum].verts[i].y){
            ymax = Shape[plyshapenum].verts[i].y;
        }
        if (zmin > Shape[plyshapenum].verts[i].z){
            zmin = Shape[plyshapenum].verts[i].z;
        }
        if (zmax < Shape[plyshapenum].verts[i].z){
            zmax = Shape[plyshapenum].verts[i].z;
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
	if (plyshapenum != 0)
	{
		R_d = R_d*1.3;
	}
    for(i=0;i<Shape[plyshapenum].numvertexs;i++){

        Shape[plyshapenum].verts[i].x = (float)((Shape[plyshapenum].verts[i].x - boundingboxcenter.x)/R_d);     
        Shape[plyshapenum].verts[i].y = (float)((Shape[plyshapenum].verts[i].y - boundingboxcenter.y)/R_d);
        Shape[plyshapenum].verts[i].z = (float)((Shape[plyshapenum].verts[i].z - boundingboxcenter.z)/R_d);  
                   
    }

}





