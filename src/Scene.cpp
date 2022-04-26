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

	shared_ptr<Light> light = make_shared<Light>(vec3(-2.0f,1.0f,1.0f));
	lights.push_back(light);

	shared_ptr<Sphere> redBall = make_shared<Sphere>(vec3(-0.5f, -1.0f, 1.0f), vec3(1, 1, 1), vec3(0, 0, 0), 1.0f); // pos , scale , rotation , RADIUS
	Phong red = Phong(vec3(1.0,0.0,0.0),vec3(1.0,1.0,0.5),vec3(0.1,0.1,0.1),100.0f);
	redBall->phong = red;
	shapes.push_back(redBall);

	shared_ptr<Sphere> greenBall = make_shared<Sphere>(vec3(0.5f, -1.0f, -1.0f), vec3(1, 1, 1), vec3(0, 0, 0), 1.0f); // pos , scale , rotation , RADIUS
	Phong green = Phong(vec3(0.0, 1.0, 0.0), vec3(1.0, 1.0, 0.5), vec3(0.1, 0.1, 0.1), 100.0f);
	greenBall->phong = green;
	shapes.push_back(greenBall);

	shared_ptr<Sphere> blueBall = make_shared<Sphere>(vec3(0.0f, 1.0f, 0.0f), vec3(1, 1, 1), vec3(0, 0, 0), 1.0f); // pos , scale , rotation , RADIUS
	Phong blue = Phong(vec3(0.0, 0.0, 1.0), vec3(1.0, 1.0, 0.5), vec3(0.1, 0.1, 0.1), 100.0f);
	blueBall->phong = blue;
	shapes.push_back(blueBall);

	//shared_ptr<Plane> planeTest = make_shared<Plane>(vec3(0, 0, -4.0f), vec3(1, 1, 1), vec3(0, 0, 0)); // pos , scale , rotation
	//planeTest->phong = blue;
	//planeTest->phong.kd = {1.0,1.0,1.0}; // white ?
	
	//shapes.push_back(planeTest); // virtual plane at z = -4;
}

void Scene::initDebug() {
	image = make_shared<Image>(width, height); // create the image for output
	camera = make_shared<Camera>(width, height); // create the camera

	shared_ptr<Sphere> origin = make_shared<Sphere>(vec3(0, 0.0f, 0.0f), vec3(1, 1, 1), vec3(0, 0, 0), 1.0f); // pos , scale , rotation , RADIUS
	Phong red = Phong(vec3(1.0, 0.0, 0.0), vec3(1.0, 1.0, 0.5), vec3(0.1, 0.1, 0.1), 100.0f);
	origin->phong = red;
	shapes.push_back(origin);
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

					//vec3 col = shade(hits[idx].x, hits[idx].n, hits[idx].phong);
					setPix(i, j, 255.0f*hits[idx].phong.kd); // only draw the closest hit, if there IS a hit at all
				}
			}

		}
	}
}

vec3 Scene::shade(vec3& pos, vec3& norm, Phong& phong) {
	// assume pos and norm are already in cam space?
	vec3 color = phong.ka;
	vec3 eye = normalize(0.0f - camera->position); // fragPos - camPos

	for (auto& light : lights) { // for each light
		vec3 l = normalize(light->pos - camera->position); // light vector
		vec3 cd = phong.kd * std::max(0.0f, dot(l, norm)); // diffuse

		vec3 h = normalize(l + eye); // halfway vec between eye and light vecs

		vec3 cs = phong.ks * pow(std::max(0.0f, dot(h, norm)), phong.s); // specular

		cout << "ka: " << phong.ka << "\n";
		cout << "ks: " << phong.ks << "\n";
		cout << "kd: " << phong.kd << "\n";
	
		cout << "eye: " << eye << "\n";
		cout << "l: " << eye << "\n";
		cout << "cd: " << eye << "\n";
		cout << "h: " << eye << "\n";
		cout << "cs: " << eye << "\n";

		color += (light->color * (cd + cs));
	}



	return color;
}


void Scene::setPix(int x, int y, const vec3& color) {
	image->setPixel(x, y,
		(unsigned char) color.x,
		(unsigned char) color.y,
		(unsigned char) color.z
	);
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