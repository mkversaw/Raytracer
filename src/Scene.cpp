#include "Scene.h"
#include <algorithm>

Scene::Scene() {
	this->width = -1;
	this->height = -1;

	std::cout << "default constructor used, caution is advised!\n";
}

Scene::Scene(const int width, const int height) : width(width), height(height) {}

void Scene::init() {
	image = make_shared<Image>(width, height); // create the image for output
	camera = make_shared<Camera>(width,height); // create the camera

	for (auto& shape : shapes) { // set the E matrix for each shape
		shape->setE();
	}
}

void Scene::render() {
	camera->camInit(); // initialize the {P , MV , C , V} matrices
	vector<vec3> ray; // size 2 : {pos,dir}
	vec3 col;

	vec3 colRef;
	vec3 colPhong;

	int idx;

	for (int j = 0; j < height; j++) { // for every pixel
		for (int i = 0; i < width; i++) {
			hits.clear();

			ray = camera->debugRay(i + 0.5f, j + 0.5f);

			for (auto& shape : shapes) { // raycast for every shape in scene
				shape->raycast(ray, hits);
			}

			if (!hits.empty()) {
				idx = nearestHit(hits);

				if (idx == -1) {
					std::cout << "hits wasn't empty, yet no hit found?\n";
				}
				else {
					
					if (isMesh) {
						col = shadeMesh(hits[idx].x, hits[idx].n, hits[idx].phong);
					}
					else {
						if (hits[idx].reflect) {
							if (isBlend) {
								colRef = reflectRay(hits[idx], reflectLimit, 0, ray[1]); // reflection color
								colPhong = shade(hits[idx].x, hits[idx].n, hits[idx].phong); // base phong color
								col = (0.3f * colRef) + (0.7f * colPhong); // 30% ref, 70% base phong
							}
							else {
								col = reflectRay(hits[idx], reflectLimit, 0, ray[1]); // ray[1] is the incidence dir
							}
						}
						else {
							col = shade(hits[idx].x, hits[idx].n, hits[idx].phong);
						}
					}
					
					setPix(i, j, col); // only draw the closest hit, if there IS a hit at all
				}
			}

		}
	}
}

vec3 Scene::shade(const vec3& pos, const vec3& norm, const Phong& phong) {
	// assume pos and norm are already in cam space?
	vec3 color = phong.ka;
	vec3 n = normalize(norm);

	clamper(n,-1,1); // NORMALS SHOULD BE CLAMPED WITH [-1 TO 1] !!!

	//vec3 norn = n;
	//clamper(norn);
	//norn *= 255;
	//return norn;

	vec3 eye = normalize(camera->position - pos); // camera position - intersection position

	vector<Hit> shadowHits; // put here

	float dist;
	float shadowEpsilon = 0.1f;
	bool shadow;

	for (auto& light : lights) { // for each light
		// compute shadow:
		
		shadowHits.clear();

		vec3 l = normalize(light->pos - pos); // light vector

		dist = glm::distance(light->pos, (pos + (l * shadowEpsilon)));

		vector<vec3> ray = { (pos + (l * shadowEpsilon)), (l) }; // direction -> end point - start point

		shadow = false;
		for (auto& shape : shapes) { // raycast for every shape in scene
			if (shape->shadowCast(ray, dist)) {
				shadow = true;
				break;
			}
		}

		if (shadow) {
			continue; // skip coloring if in shadow
		}

		vec3 cd = phong.kd * std::max(0.0f, dot(l, n)); // diffuse

		vec3 h =  normalize(l + eye); // halfway vec between eye and light vecs
		
		vec3 cs = phong.ks * pow(std::max(0.0f, dot(h, n)), phong.s); // specular

		color += (light -> intensity) * (cd + cs);

	}

	color *= 255.0f;


	return color;
}

vec3 Scene::reflectRay(const Hit& hit, int refLimit, int refs, const vec3& incidence) {

	vec3 color = { 0,0,0 };

	if (refs >= refLimit) { // out of reflections :(
		return color;
	}

	// has more reflections left

	vec3 dir = normalize(glm::reflect(incidence, normalize(hit.n))); // dir = the reflection vector // MAKE SURE HIT.N IS NORMALIZED!!!!!!
	vec3 pos = hit.x + (dir * 0.05f); // position = hit spot + epsilon shift

	vector<vec3> ray = { pos,dir };
	vector<Hit> reflectHits;

	for (auto& shape : shapes) { // raycast for every shape in scene
		shape->raycast(ray, reflectHits);
	}

	if (!reflectHits.empty()) { // RECURSIVE CASE
		int minIdx;
		float minT = (float)INT_MAX;
		minIdx = -1;

		for (int i = 0; i < reflectHits.size(); i++) {
			if (reflectHits[i].t < minT && reflectHits[i].t > 0) { // make sure .t is greater than 0 !!!
				minT = reflectHits[i].t;
				minIdx = i;
			}
		}

		if (minIdx == -1) { // nothing was found, so no color
			//cout << "i dont know how this happened\n";
			return color;
		} else if (reflectHits[minIdx].reflect) { // hit a reflective surface!
			if (isBlend) { // dont forget to add the blinn of the reflect object
				return color + (0.7f * shadeReflect(reflectHits[minIdx].x, reflectHits[minIdx].n, reflectHits[minIdx].phong, -dir)) + reflectRay(reflectHits[minIdx], refLimit, refs + 1, dir);
			}
			else {
				return color + reflectRay(reflectHits[minIdx], refLimit, refs + 1, dir);
			}
		}
		else { // Hit a non reflecive surface (phong hit), return base color + phong color AND STOP REFLECTING
			return color + shadeReflect(reflectHits[minIdx].x, reflectHits[minIdx].n, reflectHits[minIdx].phong, -dir);
		}
	}

	return color; // base case of just no output 
}

vec3 Scene::shadeReflect(const vec3& pos, const vec3& norm, const Phong& phong, vec3& eye) {
	// assume pos and norm are already in cam space?
	vec3 color = phong.ka;
	vec3 n = normalize(norm);

	clamper(n, -1, 1); // NORMALS SHOULD BE CLAMPED WITH [-1 TO 1] !!!

	vector<Hit> shadowHits; // put here

	float dist;
	float shadowEpsilon = 0.1f;
	bool shadow;

	for (auto& light : lights) { // for each light
		// compute shadow:

		shadowHits.clear();

		vec3 l = normalize(light->pos - pos); // light vector

		dist = glm::distance(light->pos, (pos + (l * shadowEpsilon)));

		vector<vec3> ray = { (pos + (l * shadowEpsilon)), (l) }; // direction -> end point - start point

		shadow = false;
		for (auto& shape : shapes) { // raycast for every shape in scene
			if (shape->shadowCast(ray, dist)) {
				shadow = true;
				break;
			}
		}

		if (shadow) {
			continue; // skip coloring if in shadow
		}

		vec3 cd = phong.kd * std::max(0.0f, dot(l, n)); // diffuse

		vec3 h = normalize(l + eye); // halfway vec between eye and light vecs

		vec3 cs = phong.ks * pow(std::max(0.0f, dot(h, n)), phong.s); // specular

		color += (light->intensity) * (cd + cs);

	}

	color *= 255.0f;


	return color;
}

void Scene::clamper(vec3& v, float l, float h) {
	v.x = glm::clamp(v.x, l, h);
	v.y = glm::clamp(v.y, l, h);
	v.z = glm::clamp(v.z, l, h);
}

void Scene::setPix(int x, int y, vec3& color) {
	clamper(color, 0, 255);
	image->setPixel(x, y,
		(unsigned char) color.x,
		(unsigned char) color.y,
		(unsigned char) color.z
	);
}

int Scene::nearestHit(const vector<Hit>& hitVec) {
	float minT = hitVec[0].t;
	int minIdx = 0;

	for (int i = 1; i < hitVec.size(); i++) {
		if (hitVec[i].t < minT) {
			minT = hitVec[i].t;
			minIdx = i;
		}
	}
	return minIdx;
}

void Scene::output(const string& filename) {
	image->writeToFile(filename);
}

vec3 Scene::shadeMesh(const vec3& pos, const vec3& norm, const Phong& phong) {
	vec3 color = phong.ka; // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	vec3 n = normalize(norm);
	clamper(n, -1, 1); // NORMALS SHOULD BE CLAMPED WITH [-1 TO 1] !!!

	//vec3 norn = n;
	//vec3 n;
	//vec3 norn = normalize(norm);
	//clamper(norn);
	//norn *= 255;
	//return norm;

	vec3 eye = normalize(camera->position - pos); // camera position - intersection position

	vector<Hit> shadowHits; // put here

	float dist;
	float shadowEpsilon = 0.1f;
	bool shadow;

	for (auto& light : lights) { // for each light
		// compute shadow:

		shadowHits.clear();

		vec3 l = normalize(light->pos - pos); // light vector

		dist = glm::distance(light->pos, (pos + (l * shadowEpsilon)));
		
		vector<vec3> ray = { (pos + (l * shadowEpsilon)), (l) }; // direction -> end point - start point
		
		shadow = false;
		for (auto& shape : shapes) { // raycast for every shape in scene
			if (shape->shadowCast(ray, dist)) {
				shadow = true;
				break;
			}
		}
		
		if (shadow) {
			continue; // skip coloring if in shadow
		}

		vec3 cd = phong.kd * std::max(0.0f, dot(l, n)); // diffuse

		vec3 h = normalize(l + eye); // halfway vec between eye and light vecs

		vec3 cs = phong.ks * pow(std::max(0.0f, dot(h, n)), phong.s); // specular

		color += (light->intensity) * (cd + cs);

	}

	color *= 255.0f;
	return color;
}