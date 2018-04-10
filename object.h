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
    bool validity_check();
    void wireframe_to_object();
    void zoom(float magX, float magY, float magZ);
    void rotation(double angle_x, double angle_y, double angle_z,object* temp);
    void objreadfile(const char* path);
    
};


class projection {
    public:
    vector2* vertices;
    int nvertex; // number of vertices
    int** edges;
    vector3 pln_vector;

    projection(int n);
    //bool validity_check();
    void zoom(float magX,float magY);
    void projreadfile(const char* path);
    void generateProj(object obj,float x,float y,float z);
    void generateProj(object obj);
    //void savefile(char* path);


};

int** zeromatix(int k);
int** copymatrix(int** src,int m,int n);
//void orthographic(object* obj,projection *top,projection *side, projection*front);
//void ortho2obj(projection* top,projection* side,projection* front,object* obj);
float volume(vector3 v1,vector3 v2,vector3 v3);
vector3 crossproduct(vector3 v1,vector3 v2);
float dotproduct(vector3 v1,vector3 v2) ;
object generateObj(projection top,projection side,projection front);

#endif // OBJECT_H
