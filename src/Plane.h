#pragma  once
#ifndef PLANE_H
#define PLANE_H

#include "Shape.h"

struct Plane : Shape {

	vec3 normal = { 0,1,0 }; // hard coded base normal w/ homogen 0
	Plane();
	Plane(const vec3& p, const vec3& s, const vec3& r);
	void raycast(const vector<vec3>& ray, std::vector<Hit>& hits);
	bool shadowCast(const vector<vec3>& ray, float maxDist);
	void setE();
};

#endif