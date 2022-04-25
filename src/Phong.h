#pragma  once
#ifndef PHONG_H
#define PHONG_H

#include <glm/glm.hpp>

struct Phong {

	glm::vec3 kd; // diffuse
	glm::vec3 ks; // specular
	glm::vec3 ka; // ambient
	float s; // exponent

	Phong() {
		kd = { 1.0f,0.0f,1.0f };
		ks = { 1.0f, 1.0f, 0.5f };
		ka = { 0.1f,0.1f,0.1f };
		s = 100.0f;
	}

	Phong(glm::vec3& kd, glm::vec3& ks = {1.0f,1.0f,0.5f}, glm::vec3& ka = { 0.1f,0.1f,0.1f }, float s = 100.0f) : kd(kd), ks(ks), ka(ka), s(s) {};

};

#endif