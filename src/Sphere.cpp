#include "Sphere.h"

Sphere::Sphere() {
	pos = { 0,0,0 };
	rotation = { 0,0,0 };
	scale = { 1,1,1 };
	radius = 1.0f;
}

Sphere::Sphere(const vec3& p = { 0,0,0 }, const vec3& s = { 1,1,1 }, const vec3& r = { 0,0,0 }, const float rad = 1.0f) {
	this->pos = p;
	this->rotation = r;
	this->scale = s;
	this->radius = rad;
}

void Sphere::raycast(vector<vec3>& ray, vector<Hit>& hits) {

	////////// Task 4: Find scaled/translated sphere intersection(s)

	vec3 pc = ray[0] - pos;
	float a = dot(ray[1], ray[1]);
	float b = 2 * (dot(ray[1], pc));
	float c2 = dot(pc, pc) - pow(radius, 2);
	float d = pow(b, 2) - 4 * a * c2;

	if (d > 0) {
		float t1 = (-b - sqrt(d)) / (2 * a);
		float t2 = (-b + sqrt(d)) / (2 * a);

		vec3 x1 = ray[0] + t1 * ray[1];
		vec3 x2 = ray[0] + t2 * ray[1];

		vec3 n1 = (x1 - pos) / radius;
		vec3 n2 = (x2 - pos) / radius;

		hits.push_back({ x1,n1,t1,Phong }); 
		hits.push_back({ x2,n2,t2,Phong });
	}

}