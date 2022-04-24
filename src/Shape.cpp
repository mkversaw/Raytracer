#include "Shape.h"

Shape::Shape() {
	pos = { 0,0,0 };
	rotation = { 0,0,0 };
	scale = { 1,1,1 };
	color = { 255,0,0 };

	std::cout << "default shape construct called!\n";
}

Shape::Shape(const vec3& p, const vec3& r, const vec3& s, const vec3& c) : pos(p), rotation(r), scale(s), color(c) {
	std::cout << "parameter shape construct called!\n";
}

void Shape::raycast(vector<vec3>& ray, vector<Hit>& hits) {
	std::cout << "default shape raycast called!\n";
}


void Shape::shift(char dir, float factor) { // debugging tool
	std::cout << "shifting in direction " << dir << " by factor " << factor << "\n";
	switch (dir) {
	case 'l': // left
		pos.x -= factor;
		break;
	case 'r': // right
		pos.x += factor;
		break;
	case 'u': // up
		pos.y += factor;
		break;
	case 'd': // down
		pos.y -= factor;
		break;
	case 'f': // forward
		pos.z += factor;
		break;
	case 'b': // back
		pos.z -= factor;
		break;
	default:
		std::cout << "invalid dir char!\n";
		break;
	}
}

void Shape::debug() {
	std::cout << "///// DEBUG\n";
	std::cout << "Position: " << pos.x << " " << pos.y << " " << pos.z << "\n";
	std::cout << "Rotation: " << rotation.x << " " << rotation.y << " " << rotation.z << "\n";
	std::cout << "Scale: " << scale.x << " " << scale.y << " " << scale.z << "\n";
	std::cout << "Color: " <<  color.x << " " << color.y << " " << color.z << "\n";
	std::cout << "///// END DEBUG\n";
}