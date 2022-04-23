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

	Sphere(const vec3& p = { 0,0,0 }, const vec3& s = { 1,1,1 }, const vec3& r = { 0,0,0 }, const float& rad = 1) {
		this->pos = p;
		this->rotation = r;
		this->scale = s;
		this->radius = rad;
	}

	void raycast(const vec3 ray[2], std::vector<Hit>& hits) {
		
		////////// Task 3: Find sphere intersection(s)

		float a = dot(ray[1], ray[1]);
		float b = 2 * dot(ray[1], ray[0]);
		float c2 = dot(ray[0], ray[0]) - 1;
		float d = pow(b, 2) - 4 * a * c2;
		// assume there are no intersections, or two intersections
		if (d > 0) { // two intersections
			float t1 = (-b - sqrt(d)) / (2 * a);
			float t2 = (-b + sqrt(d)) / (2 * a);
			vec3 x1 = ray[0] + t1 * ray[1];
			vec3 x2 = ray[0] + t2 * ray[1];
			hits.push_back({ x1,x1,t1 }); // for a unit sphere at the origin, the normal is the same as the position
			hits.push_back({ x2,x2,t2 });
		}

	}
};

#endif