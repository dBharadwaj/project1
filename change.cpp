#include <stdio.h>
#include <fstream>
#include <stdarg.h>
#include <string>
#include <math.h>
#define GL_GLEXT_PROTOTYPES
#include "object.h"
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
using namespace std;

object obj(0);
object* temp;
projection proj(0);
projection top(0);
projection front(0);
projection side(0);
projection iso(0);
bool isobj=true;


// ----------------------------------------------------------
// Function Prototypes
// ----------------------------------------------------------
void display();
void specialKeys();
 
// ----------------------------------------------------------
// Global Variables
// ----------------------------------------------------------
double rotate_y=0; 
double rotate_x=0;
double rotate_z=0;

double tr_x = 0;
double tr_y = 0;
float zoom = 1;
 
// ----------------------------------------------------------
// display() Callback function
// ----------------------------------------------------------
void display(){
 
  //  Clear screen and Z-buffer
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
 
  // Reset transformations
  glLoadIdentity();
 
  // Other Transformations
  glTranslatef(tr_x,tr_y,0);      // Not included
  // glRotatef( 180, 0.0, 1.0, 0.0 );    // Not included
 
  // Rotate when user changes rotate_x and rotate_y
  if(isobj) {
    //glRotatef( rotate_x, 1.0, 0.0, 0.0 );
    //( rotate_y, 0.0, 1.0, 0.0 );
    //glRotatef( rotate_z, 0.0, 0.0, 1.0 );
    obj.rotation(rotate_x,rotate_y,rotate_z,temp);
    //obj = *temp;
  }
  else {
    glRotatef( 0, 1.0, 0.0, 0.0 );
    glRotatef( 0, 0.0, 1.0, 0.0 );
    glRotatef( 0, 0.0, 0.0, 1.0 );
    side.generateProj(*temp,0,1,0);
    front.generateProj(*temp,1,0,0);
    top.generateProj(*temp,0,0,1);
  }
    
   
  // Other Transformations
  // glScalef( 2.0, 2.0, 0.0 );          // Not included
 
  //Multi-colored side - FRONT
  //cout<<obj.nverface[3];

  int i=0; int j=1;
  //printf("%f",obj.vertices[0].x);
  if (isobj) {  

    for(i=0;i<temp->nvertex;i++){
      for(j=0;j<i;j++){
       if(temp->edges[i][j] == 1 ){ 
          glLineWidth(5);
          glBegin(GL_LINES);
          glColor3f(  0.0,  1.0,  0.0 );
          glVertex3f(temp->vertices[i].x*zoom,temp->vertices[i].y*zoom,temp->vertices[i].z*zoom);
          glVertex3f(temp->vertices[j].x*zoom,temp->vertices[j].y*zoom,temp->vertices[j].z*zoom);
          
          glEnd();
       }
      }
     }  

    for(i=0;i<temp->nface;i++){
     glBegin(GL_POLYGON);
      glColor3f(   0,  0,  1.0 );
      for(j=0;j<temp->nverface[i];j++){
        glVertex3f( temp->vertices[temp->faces[i][j]].x*zoom,temp->vertices[temp->faces[i][j]].y*zoom, temp->vertices[temp->faces[i][j]].z*zoom );
        //printf("%d",temp->faces[i][j]); 
      }
     glEnd();
  
    }
          glLineWidth(5);
          glBegin(GL_LINES);
          glColor3f(  1.0,  1.0,  0.0 );
          glVertex3f(0,0,0);
          glVertex3f(0,0,2);          
          glEnd();

          glLineWidth(5);
          glBegin(GL_LINES);
          glColor3f(  0.0,  1.0,  1.0 );
          glVertex3f(0,0,0);
          glVertex3f(0,2,0);          
          glEnd();

          glLineWidth(5);
          glBegin(GL_LINES);
          glColor3f(  1.0,  0.0,  1.0 );
          glVertex3f(0,0,0);
          glVertex3f(2,0,0);          
          glEnd();
  }

  else {
    for(i=0;i<proj.nvertex;i++){
      for(j=0;j<i;j++){
       if(proj.edges[i][j] == 1 ){ 
          glLineWidth(5);
          glBegin(GL_LINES);
          glColor3f(  0.0,  1.0,  0.0 );
          glVertex2f(proj.vertices[i].x*zoom,proj.vertices[i].y*zoom);
          glVertex2f(proj.vertices[j].x*zoom,proj.vertices[j].y*zoom);          
          glEnd();
       }
      }
     }  
          glLineWidth(5);
          glBegin(GL_LINES);
          glColor3f(  1.0,  1.0,  0.0 );
          glVertex2f(0,0);
          glVertex2f(0,2);          
          glEnd();

          glLineWidth(5);
          glBegin(GL_LINES);
          glColor3f(  1.0,  0.0,  1.0 );
          glVertex2f(0,0);
          glVertex2f(2,0);          
          glEnd();
  }

  glFlush();
  glutSwapBuffers();
 
}

// ----------------------------------------------------------
// processKeys() Callback Function
// ----------------------------------------------------------

void processKeys(unsigned char key,int x, int y){
  if(key=='a')
    tr_x=tr_x-0.05;
  else if(key=='d')
    tr_x=tr_x+0.05;
  else if(key=='w')
    tr_y=tr_y+0.05;
  else if(key=='s')
    tr_y=tr_y-0.05;
  else if(key=='q')
    zoom=zoom*1.1;
  else if(key=='e')
    zoom=zoom*(0.9);
  else if(key=='e')
    zoom=zoom*(0.9);
    //top.generateProj(*temp,0,0,1);
    //side.generateProj(*temp,0,1,0);
    //front.generateProj(*temp,1,0,0);
  else if(key=='t')
    {proj=top;isobj=false;}
  else if(key=='f')
    {proj=front;isobj=false; }
  else if(key=='l')
    {proj=side;isobj=false;}
  else if(key=='i')
    {proj=iso;isobj=false;}
  else if(key=='o')
    isobj=true;
  else if(key=='r')
    { tr_x=tr_x=rotate_x=rotate_y=rotate_z=0; zoom=1;}
  else if(key=='z') {
    if(isobj) 
      rotate_z += 0.2; 
  }
  else if(key=='x') {
    if(isobj) 
      rotate_z -= 0.2; 
  }
  else if(key=='u') {
  //   obj.rotation((float)rotate_x,(float)rotate_y,(float)rotate_z);  
  }
   glutPostRedisplay();

}
 
// ----------------------------------------------------------
// specialKeys() Callback Function
// ----------------------------------------------------------
void specialKeys( int key, int x, int y ) {
 
  //  Right arrow - increase rotation by 5 degree
  if (key == GLUT_KEY_RIGHT) {
    if(isobj) 
      rotate_y += 0.2; 
  }
      
 
  //  Left arrow - decrease rotation by 5 degree
  else if (key == GLUT_KEY_LEFT) {
    if(isobj)
      rotate_y -= 0.2; 
  }
 
  else if (key == GLUT_KEY_UP) {
    if(isobj) 
      rotate_x += 0.2; 
  }
 
  else if (key == GLUT_KEY_DOWN) {
    if(isobj) 
      rotate_x -= 0.2; 
  }
 
  //  Request display update
  glutPostRedisplay();
 
}
 
// ----------------------------------------------------------
// main() function
// ----------------------------------------------------------
int main(int argc, char* argv[]){

  bool is3to2 = true;
  if (is3to2) {
    isobj=true;
    obj.objreadfile("3dinp.txt");
    object k(0);
    k.objreadfile("3dinp.txt");
    temp = &k;
    top.generateProj(obj,0,0,1);
    side.generateProj(obj,0,1,0);
    front.generateProj(obj,1,0,0);
    //iso.generateProj(obj);
  }
  else {
    isobj=false;
    proj=top;
    top.projreadfile("top.txt");
    side.projreadfile("side.txt");
    front.projreadfile("front.txt");
    obj=generateObj(top,side,front);
    object k=generateObj(top,side,front);
    temp = &k;
    //iso.generateProj(obj);

  }

  //  Initialize GLUT and process user parameters
  glutInit(&argc,argv);
 
  //  Request double buffered true color window with Z-buffer
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
 
  // Create window
  glutCreateWindow("AutoCad");
 
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











/*
    obj.nvertex =5;  
    obj.vertices = (vector3*) malloc(5* sizeof(vector3));
    obj.nface = 5;
    obj.edges = (int**) malloc(5* sizeof(int*));
    obj.nverface = (int*) malloc(5* sizeof(int*));
    obj.faces = (int**) malloc(5* sizeof(int));

    //for(int k=0;k<5;k++) {
      obj.edges[0] = (int*) malloc(5* sizeof(int));
    //}
      obj.edges[1] = (int*) malloc(5* sizeof(int));
      obj.edges[2] = (int*) malloc(5* sizeof(int));
      obj.edges[3] = (int*) malloc(5* sizeof(int));
      obj.edges[4] = (int*) malloc(5* sizeof(int));

    obj.vertices[0].x=0; obj.vertices[0].y=0; obj.vertices[0].z=0.5;
    obj.vertices[1].x=0.5; obj.vertices[1].y=0.5; obj.vertices[1].z=0;
    obj.vertices[2].x=0.5; obj.vertices[2].y=-0.5; obj.vertices[2].z=0;
    obj.vertices[3].x=-0.5; obj.vertices[3].y=-0.5; obj.vertices[3].z=0;
    obj.vertices[4].x=-0.5; obj.vertices[4].y=0.5; obj.vertices[4].z=0;

    obj.edges[0][0] = 0;obj.edges[0][1] = 1;obj.edges[0][2] = 1;obj.edges[0][3] = 1;obj.edges[0][4] = 1;
    obj.edges[1][0] = 1;obj.edges[1][1] = 0;obj.edges[1][2] = 1;obj.edges[1][3] = 0;obj.edges[1][4] = 1;
    obj.edges[2][0] = 1;obj.edges[2][1] = 1;obj.edges[2][2] = 0;obj.edges[2][3] = 1;obj.edges[2][4] = 0;
    obj.edges[3][0] = 1;obj.edges[3][1] = 0;obj.edges[3][2] = 1;obj.edges[3][3] = 0;obj.edges[3][4] = 1;
    obj.edges[4][0] = 1;obj.edges[4][1] = 1;obj.edges[4][2] = 0;obj.edges[4][3] = 1;obj.edges[4][4] = 0;

    int f[5] =  {4,3,3,3,3};
    obj.nverface[0] = 4;obj.nverface[1] = 4;obj.nverface[2] = 3;obj.nverface[3] = 3;obj.nverface[4] =3;

    obj.faces[0] = (int*) malloc(f[0]* sizeof(int));
    obj.faces[1] = (int*) malloc(f[1]* sizeof(int));
    obj.faces[2] = (int*) malloc(f[2]* sizeof(int));
    obj.faces[3] = (int*) malloc(f[3]* sizeof(int));
    obj.faces[4] = (int*) malloc(f[4]* sizeof(int));
    int f0[4] = { 1,2,3,4}; obj.faces[0][0] = 1;obj.faces[0][1] = 2;obj.faces[0][2] = 3;obj.faces[0][3] = 4;
    int f1[3] = { 0,1,2};   obj.faces[1][0] = 0;obj.faces[1][1] = 1;obj.faces[1][2] = 2;
    int f2[3] = { 0,2,3};   obj.faces[2][0] = 0;obj.faces[2][1] = 2;obj.faces[2][0] = 3;
    int f3[3] = { 0,3,4};   obj.faces[3][0] = 0;obj.faces[3][1] = 3;obj.faces[3][2] = 4;
    int f4[3] = { 0,4,1};   obj.faces[4][0] = 0;obj.faces[4][1] = 4;obj.faces[4][0] = 1;   

*/   
  //object obj(0);