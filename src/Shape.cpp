#include "Shape.h"

Shape::Shape() {
	pos = { 0,0,0 };
	rotation = { 0,0,0 };
	scale = { 1,1,1 };
	phong = Phong(); // ?

	std::cout << "default shape construct called!\n";
}

Shape::Shape(const vec3& p, const vec3& r, const vec3& s) : pos(p), rotation(r), scale(s) {
	std::cout << "parameter shape construct called!\n";
}

Shape::Shape(const vec3& p, const vec3& r, const vec3& s, const Phong& pho) : pos(p), rotation(r), scale(s), phong(pho) {
	std::cout << "parameter shape construct 2 called!\n";
}

void Shape::raycast(const vector<vec3>& ray, vector<Hit>& hits) {
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

void Shape::debug(bool printColor = false) {
	std::cout << "///// DEBUG\n";
	std::cout << "Position: " << pos.x << " " << pos.y << " " << pos.z << "\n";
	std::cout << "Rotation: " << rotation.x << " " << rotation.y << " " << rotation.z << "\n";
	std::cout << "Scale: " << scale.x << " " << scale.y << " " << scale.z << "\n";
	
	if (printColor) {
		std::cout << "Color: " << "\n";
		std::cout << "Diffuse: " << phong.kd.x << " " << phong.kd.y << " " << phong.kd.z << "\n";
		std::cout << "Ambient: " << phong.ka.x << " " << phong.ka.y << " " << phong.ka.z << "\n";
		std::cout << "Specular: " << phong.ks.x << " " << phong.ks.y << " " << phong.ks.z << "\n";
		std::cout << "Specular exponent: " << phong.s << "\n";
	}

	std::cout << "///// END DEBUG\n";
}