#include <iostream>
struct vector {
	float x; float y; float z;
};
class object {
	vector* vertices;
	int num;
	int** edges;
	vector** faces; //type for faces
	object* temp; // temporary changes to the object are stored here
	
	public:
	// To display object in 3D
	void display();
	
	//To check the validity of given data.
	bool validity_check();
	
	vector* out_vertex() {
		// returns list of vertices
	}
	
	vector* out_faces() {
		// returns list of faces
	} 

	int* out_edges() {
		// returns list of edges
	}
	
	int out_num() {
		//returns no. of vertices
	}
	
	void wireframe_to_object(){
		//selecting faces to convert wire frame to object until valid 3d object is formed.
	}
	void zoom(float magnification) {
		//Zoom in and out, changes temp and displays temp
	}	
	
	void rotation(float angle_x, float angle_y, float angle_z) {
		//Rotation wrt axes x,y,z(original), changes temp and displays temp
	}
	
	void plane_project( vector normal ) {
		//returns projection of temp wrt the plane given
	}	
	
	void isometric() {
		//returns isometric projection of temp
	}
	
	void orthogonal() {
		//returns orthogonal projections of temp wrt current axes
	}
	
	void reform() {
		// if no origin in vertices then chooses one vertex as origin and transforms other vertices
	}
	void savefile(char* path){
		//save the object in path file.
	}
};

struct planevector {
	float x; float y; 
};

struct hidden_edge {
	//Structure for hidden edge
};


class projection {
	planevector* vertices;
	int num; // number of vertices
	int** labeling;
	int** edges;	
	hidden_edge* hid_edge;
	projection* temp;
	vector plane_projection;
	
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
	 
	void zoom(float magnification) {
		//Zoom in and out, changes temp and displays temp
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
	

