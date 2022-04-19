#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>

using glm::vec2;
using glm::vec3;
using glm::vec4;


Camera::Camera() {
	position = { 0.0f,0.0f,5.0f }; // default position of (0,0,5)
	rotation = { 0.0f,0.0f,0.0f }; // default rotation of none
	setFOV(45.0f); // default FOV of 45 degrees
	aspect = 1.0f; // default aspect ratio of 1.0
	width = -1;
	height = -1;

	znear = 0.1f;
	zfar = 1000.0f;
}

Camera::Camera(const int& w, const int& h) {
	position = { 0.0f,0.0f,5.0f };
	rotation = { 0.0f,0.0f,0.0f };
	setFOV(45.0f);
	aspect = 1.0f;
	width = w;
	height = h;

	znear = 0.1f;
	zfar = 1000.0f;
}

void Camera::applyProjectionMatrix(std::shared_ptr<MatrixStack> P) const {
	P->multMatrix(glm::perspective(fov, aspect, znear, zfar));
}

void Camera::applyViewMatrix(std::shared_ptr<MatrixStack> MV) const
{
	// eye: cam pos
	// target: cam pos + "forward" dir
	// up: the Y vec (0,1,0)

	MV->multMatrix(glm::lookAt(position, position + glm::vec3(forward.x, rotation.y, forward.z), up));
}


void cast() {

}

void Camera::raycast(std::shared_ptr<MatrixStack> P, std::shared_ptr<MatrixStack> V) {
	int z = 4; // hardcode for now
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			vec3 px = { x,y,z }; // pixel coords
			vec2 ndc = { // normalized device coords
				(2.0 * x) / (width - 1.0),
				(2.0 * y) / (height - 1.0)
			};

			vec4 clip = { ndc.x,ndc.y,-1,1 }; // clip coords
			vec4 eye = glm::inverse(P->topMatrix()) * clip; // eye coords
			eye.w = 1;

			vec4 world = glm::inverse(V->topMatrix()) * eye; // position in world coords

			vec4 dir = normalize(world - vec4(px, 1.0)); // direction in world coords
			
		}
	}
}