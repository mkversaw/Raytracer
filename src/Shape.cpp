#include "Shape.h"

Shape::Shape() {
	pos = { 0,0,0 };
	rotation = { 0,0,0 };
	scale = { 1,1,1 };
	color = { 1,0,0 };
};

Shape::Shape(const vec3& p, const vec3& r, const vec3& s, const vec3& c) : pos(p), rotation(r), scale(s), color(c) {}

void Shape::raycast(vector<vec3>& ray, vector<Hit>& hits)
{
	std::cout << "how did you get here?\n";
}