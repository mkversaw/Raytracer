#include <iostream>
#include <string>

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

#include "Scene.h"

// This allows you to skip the `std::` in front of C++ standard library
// functions. You can also say `using std::cout` to be more selective.
// You should never do this in a header file.
using namespace std;

int sceneSelect,width, height;

shared_ptr<Scene> scene;

//ostream& operator<<(ostream& os, const vec3& v) { // helpful
//	os << v.x << " " << v.y << " " << v.z;
//	return os;
//}

int main(int argc, char **argv)
{
	if (argc < 4) {
		cout << "Usage: A6 scene width filename/path\n";
		return 0;
	}

	sceneSelect = atoi(argv[1]);

	width = atoi(argv[2]);
	height = width;

	string filename(argv[3]);


	

	scene = make_shared<Scene>(width,height);
	scene -> init();

	if (sceneSelect == 1) {
		shared_ptr<Light> light = make_shared<Light>(vec3(-2.0f, 1.0f, 1.0f));
		scene->lights.push_back(light);

		shared_ptr<Sphere> redBall = make_shared<Sphere>(vec3(-0.5f, -1.0f, 1.0f), vec3(1, 1, 1), vec3(0, 0, 0), 1.0f); // pos , scale , rotation , RADIUS
		Phong red = Phong(vec3(1.0, 0.0, 0.0), vec3(1.0, 1.0, 0.5), vec3(0.1, 0.1, 0.1), 100.0f);
		redBall->phong = red;
		scene->shapes.push_back(redBall);

		shared_ptr<Sphere> greenBall = make_shared<Sphere>(vec3(0.5f, -1.0f, -1.0f), vec3(1, 1, 1), vec3(0, 0, 0), 1.0f); // pos , scale , rotation , RADIUS
		Phong green = Phong(vec3(0.0, 1.0, 0.0), vec3(1.0, 1.0, 0.5), vec3(0.1, 0.1, 0.1), 100.0f);
		greenBall->phong = green;
		scene->shapes.push_back(greenBall);

		shared_ptr<Sphere> blueBall = make_shared<Sphere>(vec3(0.0f, 1.0f, 0.0f), vec3(1, 1, 1), vec3(0, 0, 0), 1.0f); // pos , scale , rotation , RADIUS
		Phong blue = Phong(vec3(0.0, 0.0, 1.0), vec3(1.0, 1.0, 0.5), vec3(0.1, 0.1, 0.1), 100.0f);
		blueBall->phong = blue;
		scene->shapes.push_back(blueBall);
	}
	else if (sceneSelect == 2) {

	}

	scene -> render();
	scene -> output(filename);

	return 0;
}
