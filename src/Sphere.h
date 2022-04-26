#pragma  once
#ifndef SPHERE_H
#define SPHERE_H

#include "Shape.h"

struct Sphere : Shape {
	// use position as the center
	// scale does not apply to spheres, use radius instead
	float radius;

	Sphere();
	Sphere(const vec3& p, const vec3& s, const vec3& r, const float rad);
	void raycast(const vector<vec3>& ray, std::vector<Hit>& hits);
	void shadowCast(const vector<vec3>& ray, vector<Hit>& hits, float maxDist);
	//void shift();
};

#endif