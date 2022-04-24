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
#include "Camera.h"
#include "Image.h"
#include "Light.h"

using std::string;
using std::vector;
using std::shared_ptr;
using std::make_shared;

struct Scene {

	Sphere test;

	int width, height;
	vector<Shape> shapes; // sphere , plane , triangle
	vector<Light> lights;
	vector<Hit> hits;

	shared_ptr<Image> image;
	string filename;

	shared_ptr<Camera> camera;

	Scene();
	Scene(const int width, const int height, const string);

	void init();

	void render();

	void output();

};

#endif