#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

struct Light {
	glm::vec3 pos; // center
	glm::vec3 rotation;
	glm::vec3 scale;
	glm::vec3 color = { 0,1,0 }; // default to green
};