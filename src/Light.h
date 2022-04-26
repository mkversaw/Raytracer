#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

using glm::vec3;

struct Light {
	glm::vec3 pos; // center
	float intensity;

	Light() {
		pos = { 0,0,0 };
		intensity = 1.0f;
	}

	Light(const vec3& p, float i = 1.0f) : pos(p), intensity(i) {}; // pos , scale 

};