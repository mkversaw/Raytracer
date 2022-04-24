#pragma  once
#ifndef SPHERE_H
#define SPHERE_H

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

#include "Shape.h"

struct Sphere : Shape {
	// use position as the center
	float radius;

	Sphere();
	Sphere(const vec3& p, const vec3& s, const vec3& r, const float rad);
	void raycast(const vec3 (&ray)[2], std::vector<Hit>& hits);
};

#endif