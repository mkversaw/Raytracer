#pragma  once
#ifndef SCENE_H
#define SCENE_H

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

#include <string>

#include "Shape.h"
#include "Hit.h"

#include "Sphere.h"
#include "Plane.h"
#include "Triangle.h"

#include "Camera.h"
#include "Image.h"
#include "Light.h"

using std::string;
using std::vector;
using std::cout;

struct Scene {

	int width, height;
	vector<shared_ptr<Shape>> shapes; // must contain ptrs for polymorphism to function!
	vector<shared_ptr<Light>> lights;
	vector<Hit> hits;

	shared_ptr<Image> image;

	shared_ptr<Camera> camera;


	bool isMesh = false;

	shared_ptr<Sphere> boundingSphere;

	bool isBlend = false;

	int reflectLimit = 3;

	Scene();
	Scene(const int width, const int height);

	void init();

	void render();
	//void renderMesh();

	void renderAA4X();
	void renderAA16X();

	void output(const string& filename);

	int nearestHit(const vector<Hit>& hitVec);

	void setPix(int x, int y, vec3& color);

	vec3 shade(const vec3& pos, const vec3& norm, const Phong& phong);

	vec3 shadeMesh(const vec3& pos, const vec3& norm, const Phong& phong);

	vec3 shadeReflect(const vec3& pos, const vec3& norm, const Phong& phong, vec3& eye);

	vec3 reflectRay(const Hit& hit, int refLimit, int refs, const vec3& incidence);

	void clamper(vec3& v, float l = 0.0f, float h = 1.0f);
};

#endif