#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

// Function Prototypes
void display();
//void specialKeys();
// Global Variables
double rotate_y=0; 
double rotate_x=0;

typedef struct vertex3{
	int x,y,z;
}v3;
int tr_x,tr_y,zoom;

v3 *vertex;
 int a,b;
 int nvertex,nface;
 int* nverface;
 int **edge,**faces;

/* int faces[0][4]={4,3,2,1}; nverface[0]=4;
int	faces[1][3]={0,4,2}; nverface[1]=3;
int	faces[2][3]={0,3,4}; nverface[2]=3;
int	faces[3][3]={0,2,1}; nverface[3]=3;
int	faces[4][3]={0,3,1}; nverface[4]=3;	

int	edge[0][5] = { 0,1,1,1,1};
int	edge[1][5] = { 1,0,1,1,0};
int	edge[2][5] = { 1,1,0,0,1};
int	edge[3][5] = { 1,1,0,0,1};
int	edge[4][5] = { 1,0,1,1,0};*/
void processKeys(unsigned char key,int x, int y){
	tr_x=0;
tr_y=0;
zoom=1;
	if(key=='a')
		tr_x=tr_x-0.5;
	if(key=='d')
		tr_x=tr_x+0.5;
	if(key=='w')
		tr_y=tr_y+0.5;
	if(key=='s')
		tr_y=tr_y-0.5;
	if(key=='z')
		zoom=zoom*1.6;
	if(key=='x')
		zoom=zoom*(0.625);
}
void specialKeys( int key, int x, int y ) {
 
//  Right arrow - increase rotation by 5 degree
if (key == GLUT_KEY_RIGHT)
  rotate_y += 5;
 
//  Left arrow - decrease rotation by 5 degree
else if (key == GLUT_KEY_LEFT)
  rotate_y -= 5;
 
else if (key == GLUT_KEY_UP)
  rotate_x += 5;
 
else if (key == GLUT_KEY_DOWN)
  rotate_x -= 5;
 
//  Request display update
glutPostRedisplay();
 
}

int main(int argc, char* argv[]){
 
 
 /*scanf("%d%d",&nvertex,&nface);
 for(a=0;a<nvertex;a++){
	 scanf("%d%d%d",&vertex[a].x,&vertex[a].y,&vertex[a].z);
 }
 for(a=0;a<nvertex;a++){
	 for(b=0;b<nvertex;b++){
		 scanf("%d",&edge[a][b]);
	 }
 }
 for(a=0;a<nface;a++){
	 scanf("%d",&nverface[a]);
	 for(b=0;b<nverface[a];b++){
		 scanf("%d",&faces[a][b]);
 }
}*/
	/*nvertex=5;
	nface=5;
	vertex[0].x=0;
	vertex[0].y=0;
	vertex[0].z=2;
	vertex[1].x=1;
	vertex[1].y=1;
	vertex[1].z=0;
	vertex[2].x=1;
	vertex[2].y=-1;
	vertex[2].z=0;
	vertex[3].x=-1;
	vertex[3].y=1;
	vertex[3].z=0;
	vertex[4].x=-1;
	vertex[4].y=-1;
	vertex[4].z=0;
	/*faces[0]={4,3,2,1}; nverface[0]=4;
	faces[1]={0,4,2}; nverface[1]=3;
	faces[2]={0,3,4}; nverface[2]=3;
	faces[3]={0,2,1}; nverface[3]=3;
	faces[4]={0,3,1}; nverface[4]=3;	

	edge[0] = { 0,1,1,1,1};
	edge[1] = { 1,0,1,1,0};
	edge[2] = { 1,1,0,0,1};
	edge[3] = { 1,1,0,0,1};
	edge[4] = { 1,0,1,1,0};*/
	

	/*nvertex=3;
	nface=1;
	vertex = (v3 *)malloc(10*sizeof(v3));
	vertex[0].x=0;
	vertex[0].y=0;
	vertex[0].z=0;
	vertex[1].x=1;
	vertex[1].y=0;
	vertex[1].z=0;
	vertex[2].x=0;
	vertex[2].y=1;
	vertex[2].z=0; */
	//**faces
	vertex = (v3 *)malloc(10*sizeof(v3));
	faces = (int **)malloc(8*sizeof(int *));
	for(int i = 0;i<8;i++){
		faces[i] = (int *)malloc(10*sizeof(int));
	}
	nverface = (int *)malloc(10*sizeof(int));
	
	/*faces[0][0]=0;nverface[0]=3;
	faces[0][1]=1;
	faces[0][2]=2;
	*/
	edge = (int **)malloc(8*sizeof(int *));
	for( int i = 0;i<8;i++){
		edge[i] = (int *)malloc(10*sizeof(int));
	}
	
	/*edge[0][0]=0;
	edge[0][1]=1;
	edge[0][2]=1;
	edge[1][0]=1;
 	edge[1][1]=0;
 	edge[1][2]=1;
 	edge[2][0]=1;
 	edge[2][1]=1;
 	edge[2][2]=0;*/
   

 scanf("%d%d",&nvertex,&nface);
 for(a=0;a<nvertex;a++){
	 scanf("%d%d%d",&vertex[a].x,&vertex[a].y,&vertex[a].z);
 }
 for(a=0;a<nvertex;a++){
	 for(b=0;b<nvertex;b++){
		 scanf("%d",&edge[a][b]);
	 }
 }
 for(a=0;a<nface;a++){
	 scanf("%d",&nverface[a]);
	 for(b=0;b<nverface[a];b++){
		 scanf("%d",&faces[a][b]);
     }
 }

//  Initialize GLUT and process user parameters
glutInit(&argc,argv);
 
//  Request double buffered true color window with Z-buffer
glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

// Create window
glutCreateWindow("Awesome Cube");

//  Enable Z-buffer depth test
glEnable(GL_DEPTH_TEST);

// Callback functions
glutDisplayFunc(display);
glutSpecialFunc(specialKeys);
glutKeyboardFunc(processKeys);


//  Pass control to GLUT for events
glutMainLoop();
 
//  Return to OS
return 0;
 
}


void display(){
 
//  Clear screen and Z-buffer
glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

// Reset transformations
  glLoadIdentity();
  
// Rotate when user changes rotate_x and rotate_y
  glRotatef( rotate_x, 1.0, 0.0, 0.0 );
  glRotatef( rotate_y, 0.0, 1.0, 0.0 );
   //glScalef(zoom,zoom,zoom);
  glTranslatef(tr_x,tr_y,0);
  int i,j;
  for(i=0;i<nface;i++){
	 glBegin(GL_POLYGON);
		glColor3f(   1.0,  1.0,  1.0 );
		for(j=0;j<nverface[i];j++){
			glVertex3f( vertex[faces[i][j]].x,vertex[faces[i][j]].y, vertex[faces[i][j]].z );
		}
	 glEnd();
  }
  
  for(i=0;i<nvertex;i++){
	  for(j=0;j<i;j++){
		if(edge[i][j]=1){

			glLineWidth(1);
			glBegin(GL_LINES);
			glColor3f(   1.0,  1.0,  0.0 );
			glVertex3f(vertex[i].x,vertex[i].y,vertex[i].z);
			glVertex3f(vertex[j].x,vertex[j].y,vertex[j].z);
			glEnd();
		}
	  }
  }
  

  
  
  glFlush();
glutSwapBuffers();
 
}

