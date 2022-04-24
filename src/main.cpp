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

static void init() {
	camera = Camera(3, 3);
	image = make_shared<Image>(width, height);
	test = Sphere(vec3(0,0,0),vec3(1,1,1),vec3(0,0,0)); // pos , rot , scale
}

static void render() {
	for (int j = 0; j < height; j++) {
		for (int i = width; i > 0; i--) {
			hits.clear();
			camera.raycast(i - 0.5f, j + 0.5f);
			test.raycast(camera.ray,hits);
			if (hits.size() > 0) {
				image->setPixel(i, j, 255, 0, 0);
			}
		}
	}
}

ostream& operator<<(ostream& os, const vec3& v) { // helpful
	os << v.x << " " << v.y << " " << v.z;
	return os;
}

int main(int argc, char **argv)
{
	if (argc < 4) {
		cout << "Usage: L01 filename width height" << endl;
		return 0;
	}

	string filename(argv[1]);
	width = atoi(argv[2]);
	height = atoi(argv[3]);
	
	init();
	render();
	for (auto& h : hits) { // only keep the one with the smallest t, then record its parameters
		cout << "x: " << h.x << " " << "n: " << h.n << " " << "t: " << h.t << "\n";
	}


	image->writeToFile(filename);
	return 0;
}
