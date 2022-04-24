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
	camera = make_shared<Camera>(width,height); // create the camera
	shared_ptr<Sphere> temp = make_shared<Sphere>(vec3(0, 0, 0), vec3(1, 1, 1), vec3(0, 0, 0), 1.0f); // pos , rot , scale , RADIUS
	shapes.push_back(temp);
}

void Scene::render() {
	camera->camInit(); // initialize the {P , MV , C , V} matrices
	vector<vec3> ray; // size 2 : {pos,dir}

	for (int j = 0; j < height; j++) { // for every pixel
		for (int i = width; i > 0; i--) {
			hits.clear();
			ray = camera -> getRay(i - 0.5f, j + 0.5f);

			for (auto& shape : shapes) { // raycast for every shape in scene
				shape->raycast(ray, hits);
			}

			if (hits.size() > 0) {
				image -> setPixel(i, j, 255, 0, 0);
			}
		}
	}
}

void Scene::output() {
	image->writeToFile(filename);
}