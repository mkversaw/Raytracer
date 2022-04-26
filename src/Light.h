#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

using glm::vec3;

struct Light {
	glm::vec3 pos; // center
	glm::vec3 color; // default to green
	float intensity;

	Light() {
		pos = { 0,0,0 };
		color = { 0,1,0 };
		intensity = 1.0f;
	}

	Light(const vec3& p, const vec3& col = vec3(0,1,0), float i = 1.0f) : pos(p), color(col), intensity(i) {}; // pos , scale 

};