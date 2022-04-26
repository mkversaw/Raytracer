#pragma  once
#ifndef PLANE_H
#define PLANE_H

#include "Shape.h"

struct Plane : Shape {

	Plane();
	Plane(const vec3& p, const vec3& s, const vec3& r);
	void raycast(const vector<vec3>& ray, std::vector<Hit>& hits);
	//void shift();
};

#endif