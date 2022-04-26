#include <iostream>
#include <string>

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

#include "Scene.h"

// This allows you to skip the `std::` in front of C++ standard library
// functions. You can also say `using std::cout` to be more selective.
// You should never do this in a header file.
using namespace std;

int width, height;

shared_ptr<Scene> scene;

//ostream& operator<<(ostream& os, const vec3& v) { // helpful
//	os << v.x << " " << v.y << " " << v.z;
//	return os;
//}

int main(int argc, char **argv)
{
	if (argc < 4) {
		cout << "Usage: A6 filename width height\n";
		return 0;
	}

	string filename(argv[1]);
	width = atoi(argv[2]);
	height = atoi(argv[3]);

	vec3 dir;
	float px,py;

	//for (int j = 0; j < height; j++) { // for every pixel
	//	for (int i = width - 1; i >= 0; i--) {
	//		cout << i + 0.5 << " " << j + 0.5 << "\n";
	//		px = i + 0.5;
	//		py = j + 0.5;
	//		dir = { px,px * tan(45 / width),-1 };
	//		cout << dir << "\n";
	//	}
	//}

	//for (int j = 0; j < height; j++) { // for every pixel
	//	for (int i = width - 1; i > 0; i--) {
	//		cout << i - 0.5f << " " << j + 0.5f << "\n";
	//	}
	//}

	scene = make_shared<Scene>(width,height);
	scene -> init();

	//scene->shapes[0]->debug();

	//scene->shapes[0]->shift('f', 0.5f);

	scene -> render();
	scene -> output(filename);

	//scene->shapes[0]->debug();
	
	return 0;
}
