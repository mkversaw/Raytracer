#include <iostream>
#include <string>
#include "Camera.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

#include "Image.h"
#include "Shape.h"
#include "Sphere.h"
#include "Scene.h"

// This allows you to skip the `std::` in front of C++ standard library
// functions. You can also say `using std::cout` to be more selective.
// You should never do this in a header file.
using namespace std;

Sphere test;
vector<Hit> hits;
shared_ptr<Image> image;

int width, height;

Camera camera;

shared_ptr<Scene> scene;

ostream& operator<<(ostream& os, const vec3& v) { // helpful
	os << v.x << " " << v.y << " " << v.z;
	return os;
}

int main(int argc, char **argv)
{
	if (argc < 4) {
		cout << "Usage: A6 filename width height" << endl;
		return 0;
	}

	string filename(argv[1]);
	width = atoi(argv[2]);
	height = atoi(argv[3]);
	
	//init();
	//render();
	//for (auto& h : hits) { // only keep the one with the smallest t, then record its parameters
	//	cout << "x: " << h.x << " " << "n: " << h.n << " " << "t: " << h.t << "\n";
	//}

	scene = make_shared<Scene>(width,height,filename);
	
	scene -> init();
	scene -> render();
	scene -> output();
	
	return 0;
}
