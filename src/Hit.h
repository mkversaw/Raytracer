#pragma  once
#ifndef HIT_H
#define HIT_H

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include "Phong.h"

struct Hit
{
	Hit() : x(0), n(0), t(0), phong() {}
	Hit(const glm::vec3& x, const glm::vec3& n, float t, const Phong& c) { this->x = x; this->n = n; this->t = t; this->phong = phong; }
	glm::vec3 x; // position
	glm::vec3 n; // normal
	float t; // distance

	Phong phong; // color
};

//inline bool sortHit(const Hit& h1, const Hit& h2) {
//	return h1.t < h2.t;
//}

#endif