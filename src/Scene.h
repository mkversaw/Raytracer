#pragma  once
#ifndef SCENE_H
#define SCENE_H

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

#include "Shape.h"
#include "Hit.h"
#include "Sphere.h"
#include "Camera.h"

struct Scene {

	int width, height;
	Camera camera;


	Scene() {

	}

	void init();

	void render();

};

#endif