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

void Plane::raycast(const vector<vec3>& ray, vector<Hit>& hits) {

	////////// Task 2: Find plane intersection

	float t = dot(normal, (pos - ray[0])) / (dot(normal, ray[1]));
	vec3 x = ray[0] + t * ray[1];
	if (t < 0) {
		return;
	}
	hits.push_back({ x,normal,t,phong,reflective });

}

bool Plane::shadowCast(const vector<vec3>& ray, float maxDist) {
	float t = dot(normal, (pos - ray[0])) / (dot(normal, ray[1]));
	vec3 x = ray[0] + t * ray[1];

	if (t > 0 && t < maxDist) {
		return true;
	}
	return false;
}

void Plane::setE() {
	auto M = make_shared<MatrixStack>();

	M->translate(pos);

	M->rotate(rotation.x, 1, 0, 0); // handle rotation for x,y,z
	M->rotate(rotation.y, 0, 1, 0);
	M->rotate(rotation.z, 0, 0, 1);

	M->scale(scale);

	this->E = M->topMatrix();
	this->invE = inverse(E);
}