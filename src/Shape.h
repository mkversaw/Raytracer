#pragma  once
#ifndef SHAPE_H
#define SHAPE_H

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

#include <vector>
#include <iostream>

#include "hit.h"
#include "MatrixStack.h"
#include "Phong.h"

using glm::vec2;
using glm::vec3;
using glm::vec4;
using glm::mat4;
using std::vector;
using std::shared_ptr;
using std::make_shared;
using std::cout;

inline std::ostream& operator<<(std::ostream& os, const vec3& v) { // helpful
	os << v.x << " " << v.y << " " << v.z;
	return os;
}

struct Shape {
	vec3 pos; // center
	vec3 rotation;
	vec3 scale;
	
	bool reflective = false;

	glm::mat4 E;
	glm::mat4 invE;

	Phong phong;

	Shape();
	virtual ~Shape() {}

	Shape(const vec3& p, const vec3& s, const vec3& r);
	//Shape(const vec3& p, const vec3& s, const vec3& r, const Phong& pho);

	virtual void raycast(const vector<vec3>& ray, vector<Hit>& hits);

	virtual bool shadowCast(const vector<vec3>& ray, float maxDist) { std::cout << "default shape shadowcast called!\n"; return false; };

	virtual void setE() { std::cout << "default set E called!\n"; };

	virtual void debug(bool printColor);

	void shift(char dir, float factor);
};

inline void normRGB(vec3& color) { color /= 255.0f; } // helper function

#endif