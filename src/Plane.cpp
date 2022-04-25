#include "Plane.h"

Plane::Plane() {
	pos = { 0,0,0 };
	rotation = { 0,0,0 };
	scale = { 1,1,1 };

}

Plane::Plane(const vec3& p = { 0,0,0 }, const vec3& s = { 1,1,1 }, const vec3& r = { 0,0,0 }) {
	this->pos = p;
	this->rotation = r;
	this->scale = s;

}

void Plane::raycast(vector<vec3>& ray, vector<Hit>& hits) {

	////////// Task 2: Find plane intersection

	vec3 c1 = pos; // center
	vec3 n = { 0,0,1 }; // normal
	float t = dot(n, (c1 - ray[0])) / (dot(n, ray[1]));
	vec3 x = ray[0] + t * ray[1];

	hits.push_back({ x,n,t,phong });

}