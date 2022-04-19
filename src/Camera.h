#pragma  once
#ifndef CAMERA_H
#define CAMERA_H

#include <memory>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#include <glm/gtc/constants.hpp>
#include "MatrixStack.h"

using glm::vec3;

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

	glm::vec3 up = { 0.0f, 1.0f, 0.0f }; // positive y-dir
	glm::vec3 forward = { 0.0f,0.0f,-1.0f };

	void setInitDistance(const float& z) { position.z = -std::abs(z); }
	void setAspect(const float& a) { aspect = a; };
	void setRotation(const vec3& r) { rotation = r; };
	void setWidthHeight(const int& w, const int& h) { width = w; height = h; };
	void setFOV(const float& degree) { degree * glm::pi<float>() / 180.0; };
	void applyProjectionMatrix(std::shared_ptr<MatrixStack> P) const;
	void applyViewMatrix(std::shared_ptr<MatrixStack> MV) const;
	void raycast(std::shared_ptr<MatrixStack> P, std::shared_ptr<MatrixStack> V);

};

#endif