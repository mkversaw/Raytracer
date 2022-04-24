#pragma  once
#ifndef SHAPE_H
#define SHAPE_H

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#include "hit.h"
#include "MatrixStack.h"
#include <vector>

using glm::vec2;
using glm::vec3;
using glm::vec4;
using glm::mat4;
using std::vector;

struct Shape {
	vec3 pos; // center
	vec3 rotation;
	vec3 scale;
	vec3 color = {1,0,0}; // default to red
	Shape() {
		pos = { -1,-1,-1 };
		rotation = pos;
		scale = pos;
	};
	Shape(const vec3& p, const vec3& r, const vec3& s) : pos(p), rotation(r), scale(s) {};
	virtual void raycast() {};


};



#endif