#include "object.h"
#include <stdlib.h>
#include <fstream>
#include <cmath>
using namespace std;
object::object(int n)
{
    nvertex = n;
    vertices = (vector3*) malloc(n* sizeof(vector3));
    nface = 0;
    
    edges = (int**) malloc(n* sizeof(int));
    for(int i=0; i<n; i++) {
        int x [n];
        for(int j=0;j<n;j++)
            x[j]=0;
        edges[i] = x;
    }
}

void object::zoom(float magX, float magY, float magZ){
    for( int i=0; i<nvertex; i++) {
       vertices[i].x *= magX;
       vertices[i].y *= magY;
       vertices[i].z *= magZ;
    } 
    //slave->vertices = &verti;
}

void object::rotation(double angle_x, double angle_y, double angle_z, object* temp) {
            float tempx,tempy,tempz;
            vector3* verti  = (vector3*)malloc(nvertex*sizeof(vector3));
            for(int j=0;j<nvertex;j++) {
              verti[j].x=vertices[j].x;verti[j].y=vertices[j].y;verti[j].z=vertices[j].z;
            }
            for( int i=0; i<nvertex; i++) {
                //rotation along x 
                tempy = cos(angle_x)*verti[i].y-sin(angle_x)*verti[i].z;
                tempz = sin(angle_x)*verti[i].y+cos(angle_x)*verti[i].z;
                verti[i].y=tempy; verti[i].z=tempz;
                //rotation along y
                tempx = cos(angle_y)*verti[i].x+sin(angle_y)*verti[i].z;
                tempz = -sin(angle_y)*verti[i].x+cos(angle_y)*verti[i].z;
                verti[i].x=tempx; verti[i].z=tempz;
                //rotation along z
                tempx = cos(angle_z)*verti[i].x-sin(angle_z)*verti[i].y;
                tempy = sin(angle_z)*verti[i].x+cos(angle_z)*verti[i].y;
                verti[i].x=tempx; verti[i].y=tempy;
            }
   //vertices = verti;
   temp->vertices = verti;
}

bool object::validity_check() {
    return true;
}

void object::wireframe_to_object() {

}
float dotproduct(vector3 v1,vector3 v2) {
   return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

vector3 crossproduct(vector3 v1,vector3 v2) {
  vector3 v3; 
  v3.x = v1.y * v2.z - v1.z * v2.y;
  v3.y = v1.z * v1.x - v1.x * v2.z;
  v3.z = v1.x * v2.y - v1.y * v2.x;
  return v3;
}

float volume(vector3 v1,vector3 v2,vector3 v3) {
  return dotproduct(v1,crossproduct(v2,v3));
}

int** zeromatix(int k) {
    int** hi = (int **)malloc(k*sizeof(int*));
    for(int i=0;i<k;i++) {
        int* g = (int *)malloc(k*sizeof(int));
        for(int j=0;j<k;j++) { g[j] = 0; }
        hi[i] = g;
    }
    return hi;
}

int** copymatrix(int** src,int m,int n) {
    int** hi = (int **)malloc(m*sizeof(int*));
    for(int i=0;i<m;i++) {
        int* g = (int *)malloc(n*sizeof(int));
        for(int j=0;j<n;j++) { g[j] = src[i][j]; }
        hi[i] = g;
    }
    return hi;
}
/*
void orthographic(object* obj,projection *top,projection *side, projection*front) {
    top->edges=copymatrix(obj.edges,obj.nvertex,obj.nvertex);
    side->edges=copymatrix(obj.edges,obj.nvertex,obj.nvertex);
    front->edges=copymatrix(obj.edges,obj.nvertex,obj.nvertex);

    for(int i=0;i<obj.nvertex;i++ ) {
        top->vertices[i].x=obj.vertices[i].x;
        top->vertices[i].y=obj.vertices[i].y;

        side->vertices[i].x=obj.vertices[i].x;
        side->vertices[i].y=obj.vertices[i].z;

        front->vertices[i].x=-obj.vertices[i].y;
        front->vertices[i].y=obj.vertices[i].z;
    }

    top->pln_vector.x=0;top->pln_vector.y=0;top->pln_vector.z=1.0;
    side->pln_vector.x=0;side->pln_vector.y=1;side->pln_vector.z=0;
    front->pln_vector.x=1;front->pln_vector.y=0;front->pln_vector.z=0;
}

void ortho2obj(projection* top,projection* side,projection* front,object* obj) {
   obj.nvertex = top->nvertex;
   for(int i=0;i<obj.nvertex;i++) {
       obj.vertices[i].x=top->vertices[i].x;
       obj.vertices[i].y=top->vertices[i].y;
       obj.vertices[i].z=side->vertices[i].y;
   }
   obj.edges = copymatrix(top->edges,obj.nvertex,obj.nvertex);
   obj.nface = 0;
}
*/
projection::projection(int n) {
   nvertex= n;
   vertices = (vector2*)malloc(n*sizeof(vector3));
   edges = (int**) malloc(n* sizeof(int));
   for(int i=0; i<n; i++) {
       int x [n];
       for(int j=0;j<n;j++)
           x[j]=0;
       edges[i] = x;
   }
   pln_vector.x=0;pln_vector.y=0;pln_vector.z=0;
}

void projection::zoom(float magX, float magY) {
    for( int i=0; i<nvertex; i++) {
       vertices[i].x *= magX;
       vertices[i].y *= magY;
    }
}

void object::objreadfile(const char* path) {

    ifstream infile;
    infile.open(path);
    int x; float y;
    infile>>x;
    nvertex=x;
    vertices = (vector3*) malloc(x* sizeof(vector3));
    edges = (int**) malloc(x* sizeof(int*));
    int i;
    for( i=0;i<nvertex;i++) {
        infile>>y;
        vertices[i].x=(y);
        infile>>y;
        vertices[i].y=(y);
        infile>>y;
        vertices[i].z=(y);
    }
    for(int j=0;j<nvertex;j++) {
        edges[j] = (int*) malloc(nvertex* sizeof(int));
        for(int k=0;k<nvertex;k++) {
            infile>>x;
            edges[j][k] = x;
        }
    }
    infile>>x;
    nface =x ;
    nverface = (int*) malloc(x* sizeof(int*));
    faces = (int**) malloc(x* sizeof(int*));

    for(int b=0;b<nface;b++) {
       infile>>x;
       nverface[b] = x;
       faces[b] = (int*) malloc(x* sizeof(int));
       for(int a=0;a<nverface[b];a++) {
          infile>>x;
          faces[b][a] = x;
       }
    } 
    infile.close();
}


void projection::projreadfile(const char* path) {
  ifstream infile;
    infile.open(path);
    int x; float y;
    infile>>x;
    nvertex=x;
  // projection proj1 = projection(x);
   //projection* proj = &proj1;
    vertices = (vector2*) malloc(x* sizeof(vector2));
    edges = (int**) malloc(x* sizeof(int*));
    int i,j,k;
    for( i=0;i<nvertex;i++) {
        infile>>y;
        vertices[i].x=(y);
        infile>>y;
        vertices[i].y=(y);
        
    }
   for( j=0;j<nvertex;j++) {
        edges[j] = (int*) malloc(nvertex* sizeof(int));
        for( k=0;k<nvertex;k++) {
            infile>>x;
            edges[j][k] = x;
        }
    }

   infile>>y;   pln_vector.x=y;
   infile>>y;   pln_vector.y=y;
   infile>>y;   pln_vector.z=y;
   infile.close();
   
}

void projection::generateProj(object obj,float x,float y,float z) {
   nvertex = obj.nvertex;
   if (x==0 && y==0 && z==1) {
    for(int i=0;i<obj.nvertex;i++) {
        vertices[i].x=obj.vertices[i].x;
        vertices[i].y=obj.vertices[i].y;

    }
   }
   else if (x==0 && y==1 && z==0) {
    for(int i=0;i<obj.nvertex;i++) {
        vertices[i].x=obj.vertices[i].z;
        vertices[i].y=-obj.vertices[i].x;
    }
   }    
   else if (x==1 && y==0 && z==0) {
    for(int i=0;i<obj.nvertex;i++) {
        vertices[i].x=-obj.vertices[i].z;
        vertices[i].y=obj.vertices[i].y;
    }
   }
   else {
       //To be continued
   }
   pln_vector.x=x;pln_vector.y=y;pln_vector.z=z;
   edges = copymatrix(obj.edges,obj.nvertex,obj.nvertex);
}

void projection::generateProj(object obj) {
  //For Isometric Projection
}

object generateObj(projection top,projection side,projection front) {
   object obj(0);
   obj.nvertex = top.nvertex;
   obj.vertices = (vector3*) malloc(obj.nvertex* sizeof(vector3));
   for(int i=0;i<obj.nvertex;i++) {
       obj.vertices[i].x=top.vertices[i].x;
       obj.vertices[i].y=top.vertices[i].y;
       obj.vertices[i].z=side.vertices[i].x;
   }
   obj.edges = copymatrix(top.edges,obj.nvertex,obj.nvertex);
   obj.nface = 0; 
   return obj;  
}