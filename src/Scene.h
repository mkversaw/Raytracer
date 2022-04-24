#pragma  once
#ifndef SCENE_H
#define SCENE_H

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

#include <iostream>
#include <vector>
#include "Shape.h"
#include "Hit.h"
#include "Sphere.h"
#include "Camera.h"
#include "Image.h"
#include "Light.h"

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
	Camera camera;

	Scene(const int& width, const int& height);

	void init();

	void render();

};

#endif