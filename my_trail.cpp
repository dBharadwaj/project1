#include <fstream>
#include <iostream>
#include <cmath>
using namespace std;
struct vector3 {
    float x; float y; float z;
};

struct vector2 {
    float x; float y;
};

class object
{ public:
        vector3* vertices;
        int nvertex,nface;
        int* nverface;
        int** edges;
        int** faces; //type for faces
        //object* slave; // temporary changes to the object are stored here
 object(int n)
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


void rotation(double angle_x, double angle_y, double angle_z,object* temp) {
            float tempx,tempy,tempz;
            
            vector3* verti  = (vector3*)malloc(nvertex*sizeof(vector3));          
            for(int j=0;j<nvertex;j++) {
              verti[j].x=vertices[j].x;verti[j].y=vertices[j].y;verti[j].z=vertices[j].z;
            } 
            //vector3 * verti = vertices;

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
   temp->vertices = verti;
}
  void objreadfile(const char* path) {

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
};


int main() {
  object obj(0);
  obj.objreadfile("3dinpwire.txt");
  obj.rotation(90.0*3.14/180,90.0*3.14/180,90.0*3.14/180);

  cout<<obj.nvertex<<"\n";
  for(int i=0;i<obj.nvertex;i++) {
    cout<<obj.vertices[i].x<<" "<<obj.vertices[i].y<<" "<<obj.vertices[i].z<<"\n";
  }

  
  return 0;
}
