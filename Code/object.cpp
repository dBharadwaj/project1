#include <iostream>
#include <cmath>
struct vector {
	float x; float y; float z;
};
class object {
	vector* vertices;
	int nvertex,nface;
	int* nverface;
	int** edges;
	int** faces; //type for faces
	object* slave; // temporary changes to the object are stored here
	
	public:
	// To display object in 3D
	void display();
	
	//To check the validity of given data.
	bool validity_check();
	
	// returns list of vertices 
	vector* out_vertex();

	// returns list of faces
	} 
	vector* out_faces();
		
	// returns list of edges
	int* out_edges(); 
	
	//returns no. of vertices
	int out_num(); 
		
	
	//selecting faces to convert wire frame to object until valid 3d object is formed.
	void wireframe_to_object();	
	
	//Zoom in and out, changes temp and displays temp
	void zoom(float magX, float magY, fload magZ){
		int nv = *(slave->nvertex);
		vector verti[nv] = *(slave->vertices);
		for( int i=0; i<nv; i++) {
			verti[i][0] *= magX;
			verti[i][1] *= magY;
			verti[i][2] *= magZ;
		} 
		slave->vertices = &verti;
	};

	//Rotation wrt axes x,y,z(original), changes temp and displays temp
	void rotation(float angle_x=0, float angle_y=0, float angle_z=0) {
		int nv = *(slave->nvertex);
		vector verti[nv] = *(slave->vertices);
		for( int i=0; i<nv; i++) {
			//verti[i][0] *= angle_x;
			verti[i][1] = cos(angle_x)*verti[i][1]-sin(angle_x)*verti[i][2];
			verti[i][2] = sin(angle_x)*verti[i][1]+cos(angle_x)*verti[i][2];

			verti[i][0] = cos(angle_y)*verti[i][0]+sin(angle_y)*verti[i][2];
			//verti[i][1] = cos(angle_x)*verti[i][1]-sin(angle_x)*verti[i][2];
			verti[i][2] = -sin(angle_y)*verti[i][0]+cos(angle_y)*verti[i][2];

			verti[i][0] = cos(angle_z)*verti[i][0]-sin(angle_z)*verti[i][1];;
			verti[i][1] = sin(angle_z)*verti[i][1]+cos(angle_z)*verti[i][1m ];
			//verti[i][2] = sin(angle_x)*verti[i][1]+cos(angle_x)*verti[i][2];

		} 
		slave->vertices = &verti;
	};
		
	
	//returns projection of temp wrt the plane given
	void plane_project( vector normal );
	
	//returns isometric projection of temp
	void isometric();
	
	//returns orthogonal projections of temp wrt current axes
	void orthogonal();
	
	// if no origin in vertices then chooses one vertex as origin and transforms other vertices
	void reform();
	
	//save the object in path file.
	void savefile(char* path);
};

struct planevector {
	float x; float y; 
};

struct hidden_edge {
	//Structure for hidden edge
};


class projection {
	planevector* vertices;
	int nvertex,nverobj; // number of vertices
	int** labeling; //int[nverobj][nvertex]
	int** edges;	
	//hidden_edge* hid_edge;
	projection* slave;
	vector pln_vector;
	
	public:
	bool validity_check(){
		//To check the validity of given data.
	}

	void display() {
		// To display projection(2D)
	}
	
	planevector* out_vertex() {
		// returns list of vertices
	}
	
	hidden_edge* out_hid_edge() {
		// returns list of hidden edges
	}

	int* out_edges() {
		// returns list of edges
	}
	
	int out_num() {
		//returns no. of vertices
	}
	 
	void zoom(float magX,float magY) {
		//Zoom in and out, changes temp and displays temp
		int nv = *(slave->nvertex);
		vector verti[nv] = *(slave->vertices);
		for( int i=0; i<nv; i++) {
			verti[i][0] *= magX;
			verti[i][1] *= magY;
			//verti[i][2] *= magZ;
		} 
		slave->vertices = &verti;
	}
	void savefile(char* path){
		//save the projection in path file.
	}
};	

bool check(projection* plane){
		//checking if the data is sufficient to create unique 3d object.
	}

object wireframe(projection* plane){
		//Generate wire frame.
	}

int main() {
	//Main
}
	