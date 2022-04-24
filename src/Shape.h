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

using glm::vec2;
using glm::vec3;
using glm::vec4;
using glm::mat4;
using std::vector;



struct Shape {
	vec3 pos; // center
	vec3 rotation;
	vec3 scale;
	vec3 color; // defaults to red

	Shape();
	virtual ~Shape() {}

	Shape(const vec3& p, const vec3& r, const vec3& s, const vec3& c);
	virtual void raycast(vector<vec3>& ray, vector<Hit>& hits);

	void shift(char dir, float factor);

	virtual void debug();
};

inline void normRGB(vec3& color) { color /= 255.0f; } // helper function

#endif