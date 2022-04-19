#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <iostream>

using glm::vec2;
using glm::vec3;
using glm::vec4;
using glm::mat4;

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

	//MV->translate(position);
	//MV->rotate(rotation.y, glm::vec3(1.0f, 0.0f, 0.0f));
	//MV->rotate(rotation.x, glm::vec3(0.0f, 1.0f, 0.0f));
}


void Camera::cast() {

	auto MV = std::make_shared<MatrixStack>();
	MV->loadIdentity();
	applyProjectionMatrix(MV);

	mat4 P = MV->topMatrix();
	
	MV->loadIdentity();
	applyViewMatrix(MV);

	mat4 V = MV->topMatrix();
	mat4 C = inverse(V);

	vec3 ray[2];

	std::cout << "fov: " << height << "\n";

	ray[0] = vec3(C[3][0], C[3][1], C[3][2]);

	// x , y = 1.5 -> the middle of the middle pixel

	float x = 1.5;
	//float y = tan(degRad(45));
	float y = 1.5;
	std::cout << "y: " << y << "\n";

	vec2 ndc = { // normalized device coords
		((2.0 * x) / (width))-1.0,
		1.0 - ((2.0 * y) / (height))
	};

	std::cout << ndc.x << " " << ndc.y << "\n";

	vec4 clip = { ndc.x,ndc.y,-1.0,1.0 }; // clip coords

	vec4 eye = glm::inverse(P) * clip; // eye coords
	eye.w = 1;

	std::cout << eye.x << " " << eye.y << " " << eye.z << "\n";

	vec4 world = C * eye; // position in world coords

	std::cout << world.x << " " << world.y << " " << world.z << "\n";

	vec4 dir = normalize(world - vec4(ray[0], 1.0)); // direction in world coords
	ray[1] = dir;
	//vec4 test = world - vec4((vec3(0, 1, 0), 1.0));
	//std::cout << "x: " << ray[0].x << " y: " << ray[0].y << " z: " << ray[0].z << "\n";
	std::cout << "x: " << ray[1].x << " y: " << ray[1].y << " z: " << ray[1].z << "\n";
	//std::cout << "x: " << test.x << " y: " << test.y << " z: " << test.z << "\n";
}

void Camera::raycast(std::shared_ptr<MatrixStack> P, std::shared_ptr<MatrixStack> V) {
	int z = 4; // hardcode for now
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			vec3 px = { x,y,z }; // pixel coords
			vec2 ndc = { // normalized device coords
				((2.0 * x) / (width)-1.0),
				(1.0 - (2.0 * y) / (height))
			};

			vec4 clip = { ndc.x,ndc.y,-1,1 }; // clip coords
			vec4 eye = glm::inverse(P->topMatrix()) * clip; // eye coords
			eye.w = 1;

			vec4 world = glm::inverse(V->topMatrix()) * eye; // position in world coords

			vec4 dir = normalize(world - vec4(px, 1.0)); // direction in world coords
			
		}
	}
}