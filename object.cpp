#include "object.h"
#include <stdlib.h>
#include <fstream>
#include <cmath>

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

void object::rotation(float angle_x, float angle_y, float angle_z) {

            vector3* verti  = vertices;
            for( int i=0; i<nvertex; i++) {
                //rotation along x
                verti[i].y = cos(angle_x)*verti[i].y-sin(angle_x)*verti[i].z;
                verti[i].z = sin(angle_x)*verti[i].y+cos(angle_x)*verti[i].z;

                //rotation along y
                verti[i].x = cos(angle_y)*verti[i].x+sin(angle_y)*verti[i].z;
                verti[i].z = -sin(angle_y)*verti[i].x+cos(angle_y)*verti[i].z;

                //rotation along z
                verti[i].x = cos(angle_z)*verti[i].x-sin(angle_z)*verti[i].y;
                verti[i].y = sin(angle_z)*verti[i].x+cos(angle_z)*verti[i].y;

            }
   vertices = verti;
}

bool object::validity_check() {
    return true;
}

void object::wireframe_to_object() {

}


int** zeromatix(int k) {
    int** hi = (int **)malloc(k*sizeof(int));
    for(int i=0;i<k;i++) {
        int* g = (int *)malloc(k*sizeof(int));
        for(int j=0;j<k;j++) { g[j] = 0; }
        hi[i] = g;
    }
    return hi;
}

int** copymatrix(int** src,int m,int n) {
    int** hi = (int **)malloc(m*sizeof(int));
    for(int i=0;i<m;i++) {
        int* g = (int *)malloc(n*sizeof(int));
        for(int j=0;j<n;j++) { g[j] = src[i][j]; }
        hi[i] = g;
    }
    return hi;
}

void orthographic(object* obj,projection *top,projection *side, projection*front) {
    top->edges=copymatrix(obj->edges,obj->nvertex,obj->nvertex);
    side->edges=copymatrix(obj->edges,obj->nvertex,obj->nvertex);
    front->edges=copymatrix(obj->edges,obj->nvertex,obj->nvertex);

    for(int i=0;i<obj->nvertex;i++ ) {
        top->vertices[i].x=obj->vertices[i].x;
        top->vertices[i].y=obj->vertices[i].y;

        side->vertices[i].x=obj->vertices[i].x;
        side->vertices[i].y=obj->vertices[i].z;

        front->vertices[i].x=-obj->vertices[i].y;
        front->vertices[i].y=obj->vertices[i].z;
    }

    top->pln_vector.x=0;top->pln_vector.y=0;top->pln_vector.z=1.0;
    side->pln_vector.x=0;side->pln_vector.y=1;side->pln_vector.z=0;
    front->pln_vector.x=1;front->pln_vector.y=0;front->pln_vector.z=0;
}

void ortho2obj(projection* top,projection* side,projection* front,object* obj) {
   obj->nvertex = top->nvertex;
   for(int i=0;i<obj->nvertex;i++) {
       obj->vertices[i].x=top->vertices[i].x;
       obj->vertices[i].y=top->vertices[i].y;
       obj->vertices[i].z=side->vertices[i].y;
   }
   obj->edges = copymatrix(top->edges,obj->nvertex,obj->nvertex);
   obj->nface = 0;
}

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

object* objreadfile(char* path) {

    std::fstream infile(path, std::ios_base::in);
    int x; float y;
    infile>>x;
    object obj1 = object(x);
    object* obj = &obj1;
    for(int i=0;i<obj->nvertex;i++) {
        infile>>y;
        obj->vertices[i].x=(y);
        infile>>y;
        obj->vertices[i].y=(y);
        infile>>y;
        obj->vertices[i].z=(y);
    }
    for(int j=0;j<obj->nvertex;j++) {
        for(int k=0;k<obj->nvertex;k++) {
            infile>>x;
            obj->edges[j][k] = x;
    }
    infile>>x;
    obj->nface =x ;
    obj->nverface = (int*)malloc(obj->nvertex*sizeof(int) );
    for(int b=0;b<obj->nvertex;b++) {
       infile>>x;
       obj->nverface[b] = x;
    }
    return obj;
}


projection* projreadfile(char* path) {
   std::fstream myfile(path, std::ios_base::in);
   int x;float y;
   infile>>x;
   projection* proj = &projection(x);
   for(int i=0;i<proj->nvertex;i++) {
       infile>>y;
       proj->vertices[i].x=(y);
       infile>>y;
       proj->vertices[i].y=(y);
   }
   for(int j=0;j<proj->nvertex;j++) {
       for(int k=0;k<proj->nvertex;k++) {
           infile>>x;
           proj->edges[j][k] = x;
       }
   }

   infile>>y;   proj->pln_vector.x=y;
   infile>>y;   proj->pln_vector.y=y;
   infile>>y;   proj->pln_vector.z=y;

   return proj;
}
