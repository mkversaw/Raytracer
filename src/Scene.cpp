#include "Scene.h"
#include <algorithm>

Scene::Scene() {
	this->width = -1;
	this->height = -1;

	std::cout << "default constructor used, caution is advised!\n";
}

Scene::Scene(const int width, const int height) : width(width), height(height) {
	std::cout << "creating scene with width: " << width << " and height: " << height << "\n";
}

void Scene::init() {
	image = make_shared<Image>(width, height); // create the image for output
	camera = make_shared<Camera>(width,height); // create the camera

	shared_ptr<Sphere> sphereTest = make_shared<Sphere>(vec3(0, 0, 0), vec3(0, 0, 0), vec3(1, 1, 1), 1.0f); // pos , rot , scale , RADIUS
	shapes.push_back(sphereTest);

	shared_ptr<Plane> planeTest = make_shared<Plane>(vec3(0, 0, -4.0f), vec3(0, 0, 0), vec3(1, 1, 1)); // pos , rot , scale
	planeTest -> color = { 0,0,0 };
	shapes.push_back(planeTest); // virtual plane at z = -4;
}

void Scene::render() {
	camera->camInit(); // initialize the {P , MV , C , V} matrices
	vector<vec3> ray; // size 2 : {pos,dir}
	int idx;

	for (int j = 0; j < height; j++) { // for every pixel
		for (int i = width - 1; i >= 0; i--) {
			hits.clear();
			ray = camera -> getRay(i - 0.5f, j + 0.5f);

			for (auto& shape : shapes) { // raycast for every shape in scene
				shape->raycast(ray, hits);
			}

			if (!hits.empty()) {
				idx = nearestHit();

				if (idx == -1) {
					std::cout << "hits wasn't empty, yet no hit found?\n";
				}
				else {
					image->setPixel(i, j, hits[idx].c.x, hits[idx].c.y, hits[idx].c.z); // only draw the closest hit, if there IS a hit at all
				}
			}

		}
	}
}

int Scene::nearestHit() {
	float minT = hits[0].t;
	int minIdx = 0;

	for (int i = 1; i < hits.size(); i++) {
		if (hits[i].t < minT) {
			minT = hits[i].t;
			minIdx = i;
		}
	}
	return minIdx;
}

void Scene::output(const string& filename) {
	image->writeToFile(filename);
}