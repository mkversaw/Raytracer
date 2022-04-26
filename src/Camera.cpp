#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <iostream>

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

	MV = std::make_shared<MatrixStack>(); // !
}

void Camera::applyProjectionMatrix(std::shared_ptr<MatrixStack> P) const {
	P->multMatrix(glm::perspective(fov, aspect, znear, zfar));
}

void Camera::applyViewMatrix(std::shared_ptr<MatrixStack> MV) const
{
	// eye: cam pos
	// target: cam pos + "forward" dir (0,0,-1)
	// up: the Y vec (0,1,0)

	MV->multMatrix(glm::lookAt(position, position + glm::vec3(forward.x, rotation.y, forward.z), up));
}

void Camera::camInit() {
	MV->loadIdentity(); // resets MV without deleting its pointer
	applyProjectionMatrix(MV);

	P = MV->topMatrix();

	MV->loadIdentity();
	applyViewMatrix(MV);

	V = MV->topMatrix();
	C = glm::inverse(V);
}

/*void Camera::cast(const float& px, const float& py, std::shared_ptr<MatrixStack>& MV, mat4& P, mat4& V, mat4& C) {

	ray[0] = vec3(C[3][0], C[3][1], C[3][2]);


	//float y = tan(degRad(45));

	//std::cout << "y: " << y << "\n";

	vec2 ndc = { // normalized device coords
		((2.0 * px) / (width))-1.0,
		1.0 - ((2.0 * py) / (height))
	};

	//std::cout << ndc.x << " " << ndc.y << "\n";

	vec4 clip = { ndc.x,ndc.y,-1.0,1.0 }; // clip coords

	vec4 eye = glm::inverse(P) * clip; // eye coords
	eye.w = 1;

	//std::cout << eye.x << " " << eye.y << " " << eye.z << "\n";

	vec4 world = C * eye; // position in world coords

	//std::cout << world.x << " " << world.y << " " << world.z << "\n";

	vec4 dir = normalize(world - vec4(ray[0], 1.0)); // direction in world coords
	ray[1] = dir;

}*/

vector<vec3> Camera::getRay(const float px, const float py) {
	vector<vec3> ray = { vec3(C[3][0], C[3][1], C[3][2]), vec3(1, 1, 1) }; // place holder for ray[1]

	vec2 ndc = { // normalized device coords
		((2.0f * px) / (width)) - 1.0f,
		1.0f - ((2.0f * py) / (height))
	};

	vec4 clip = { ndc.x , ndc.y , -1.0f , 1.0f }; // clip coords

	vec4 eye = glm::inverse(P) * clip; // eye coords
	eye.w = 1.0f;

	vec4 world = C * eye; // position in world coords

	ray[1] = normalize(world - vec4(ray[0] , 1.0f)); // direction in world coords

	return ray;
}



vector<vec3> Camera::debugRay(const float px, const float py) {
	vector<vec3> ray = {position, vec3(1, 1, 1) }; // place holder for ray[1]
	
	//vector<vec3> ray = { position,vec3(1,1,1) }; // all rays ome from cam pos

	vec2 ndc = { // normalized device coords
		((2.0f * px) / (width)) - 1.0f,
		1.0f - ((2.0f * py) / (height))
	};

	vec4 clip = { ndc.x , ndc.y , -1.0f , 1.0f }; // clip coords

	clip *= tan(fov / 2.0f);

	vec4 eye = glm::inverse(P) * clip; // eye coords
	eye.w = 1.0f;

	vec4 world = C * eye; // position in world coords

	ray[1] = normalize(world - vec4(ray[0], 1.0f)); // direction in world coords

	return ray;
}
