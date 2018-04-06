#ifndef OBJECT_H
#define OBJECT_H

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


    object(int n);
    //void display();
    bool validity_check();
    void wireframe_to_object();
    void zoom(float magX, float magY, float magZ);
    void rotation(float angle_x, float angle_y, float angle_z);
    //void plane_project( vector3 normal );
    //void isometric();
    //void orthogonal();
    //void reform();
    //void savefile(char* path);
    //object* readfile(char* path);
};


class projection {
    public:
    vector2* vertices;
    int nvertex; // number of vertices
    //int** labeling; //int[nverobj][nvertex]
    int** edges;
    //projection* slave;
    vector3 pln_vector;

    projection(int n);
    bool validity_check();
    projection* readfile(char* path);
    //void display();
    vector2* out_vertex();
    void zoom(float magX,float magY);
    void savefile(char* path);


};

int** zeromatix(int k);
int** copymatrix(int** src,int m,int n);
void orthographic(object* obj,projection *top,projection *side, projection*front);
void ortho2obj(projection* top,projection* side,projection* front,object* obj);
object* objreadfile(char* path);
projection* projreadfile(char* path);
#endif // OBJECT_H
