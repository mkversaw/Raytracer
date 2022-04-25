#pragma  once
#ifndef CAMERA_H
#define CAMERA_H

#include <memory>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#include <vector>
#include <glm/gtc/constants.hpp>
#include "MatrixStack.h"

using std::vector;
using glm::vec3;
using glm::mat4;

struct Camera {

	Camera();
	Camera(const int& w, const int& h);

	vec3 position;
	vec3 rotation;

	float fov;
	float aspect;
	int width;
	int height;

	float znear;
	float zfar;

	std::shared_ptr<MatrixStack> MV;
	glm::mat4 P;
	glm::mat4 V;
	glm::mat4 C;

	glm::vec3 up = { 0.0f, 1.0f, 0.0f }; // positive y-dir
	glm::vec3 forward = { 0.0f,0.0f,-1.0f };

	void setInitDistance(const float& z) { position.z = -std::abs(z); }
	void setAspect(const float& a) { aspect = a; };
	void setRotation(const vec3& r) { rotation = r; };
	void setWidthHeight(const int& w, const int& h) { width = w; height = h; };
	float degRad(const float& degree) { return (degree * glm::pi<float>() / 180.0f); };
	void setFOV(const float& degree) { fov = ( degree * glm::pi<float>() / 180.0f); };

	void applyProjectionMatrix(std::shared_ptr<MatrixStack> P) const;
	void applyViewMatrix(std::shared_ptr<MatrixStack> MV) const;

	void camInit();
	vector<vec3> getRay(const float px, const float py);
};

#endif