#pragma  once
#ifndef SCENE_H
#define SCENE_H

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

#include <string>

#include "Shape.h"
#include "Hit.h"

#include "Sphere.h"
#include "Plane.h"

#include "Camera.h"
#include "Image.h"
#include "Light.h"

using std::string;
using std::vector;
using std::shared_ptr;
using std::make_shared;
using std::cout;

struct Scene {

	int width, height;
	vector<shared_ptr<Shape>> shapes; // must contain ptrs for polymorphism to function!
	vector<shared_ptr<Light>> lights;
	vector<Hit> hits;

	shared_ptr<Image> image;

	shared_ptr<Camera> camera;

	Scene();
	Scene(const int width, const int height);

	void init();

	void render();

	void output(const string& filename);

	int nearestHit();

	void setPix(int x, int y, const vec3& color);

	vec3 shade(vec3& pos, vec3& norm, Phong& phong);

	void initDebug();

};

#endif