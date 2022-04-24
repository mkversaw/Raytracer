#include "Scene.h"

Scene::Scene() {
	this->width = -1;
	this->height = -1;

	std::cout << "default constructor used, caution is advised!\n";
}

Scene::Scene(const int width, const int height, const string filename) : width(width), height(height), filename(filename) {
	std::cout << "creating scene with width: " << width << " and height: " << height << "\n";
}

void Scene::init() {
	image = make_shared<Image>(width, height); // create the image for output
	camera = Camera(width,height); // create the camera
	test = Sphere(vec3(0, 0, 0), vec3(1, 1, 1), vec3(0, 0, 0),1); // pos , rot , scale , RADIUS
}

void Scene::render() {
	for (int j = 0; j < height; j++) {
		for (int i = width; i > 0; i--) {
			hits.clear();
			camera.raycast(i - 0.5f, j + 0.5f);
			test.raycast(camera.ray, hits);
			if (hits.size() > 0) {
				image->setPixel(i, j, 255, 0, 0);
			}
		}
	}
}

void Scene::output() {
	image->writeToFile(filename);
}