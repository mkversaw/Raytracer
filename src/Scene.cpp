#include "Scene.h"
#include <algorithm>

Scene::Scene() {
	this->width = -1;
	this->height = -1;

	std::cout << "default constructor used, caution is advised!\n";
}

Scene::Scene(const int width, const int height) : width(width), height(height) {
	std::cout << "creating scene with width: " << width << " and height: " << height << "\n";
}

void Scene::init() {
	image = make_shared<Image>(width, height); // create the image for output
	camera = make_shared<Camera>(width,height); // create the camera

	for (auto& shape : shapes) { // set the E matrix for each shape
		shape->setE();
	}
}

void Scene::initDebug() {
	image = make_shared<Image>(width, height); // create the image for output
	camera = make_shared<Camera>(width, height); // create the camera

	shared_ptr<Sphere> origin = make_shared<Sphere>(vec3(0, 0.0f, 0.0f), vec3(1, 1, 1), vec3(0, 0, 0), 1.0f); // pos , scale , rotation , RADIUS
	Phong red = Phong(vec3(1.0, 0.0, 0.0), vec3(1.0, 1.0, 0.5), vec3(0.1, 0.1, 0.1), 100.0f);
	origin->phong = red;
	shapes.push_back(origin);
}

void Scene::render() {
	camera->camInit(); // initialize the {P , MV , C , V} matrices
	vector<vec3> ray; // size 2 : {pos,dir}
	vec3 col;
	int idx;

	for (int j = 0; j < height; j++) { // for every pixel
		for (int i = width - 1; i > 0; i--) {
			hits.clear();

			ray = camera->debugRay(i - 0.5f, j + 0.5f);

			for (auto& shape : shapes) { // raycast for every shape in scene
				shape->raycast(ray, hits);
			}

			if (!hits.empty()) {
				idx = nearestHit(hits);

				if (idx == -1) {
					std::cout << "hits wasn't empty, yet no hit found?\n";
				}
				else {
					
					if (hits[idx].reflect) {
						col = reflectRay(hits[idx], 3, 0, ray[1]); // ray[1] is the incidence dir
						//cout << col << "\n";
					}
					else {
						col = shade(hits[idx].x, hits[idx].n, hits[idx].phong);
					}
					
					//cout << col << "\n";
					//setPix(i, j, 255.0f*hits[idx].phong.kd); // only draw the closest hit, if there IS a hit at all
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

	vec3 norn = n;
	clamper(norn);
	norn *= 255;
	return norn;

	vec3 eye = normalize(camera->position - pos); // camera position - intersection position

	vector<Hit> shadowHits; // put here
	vec3 dir;
	int idx;
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

		//cout << "ka: " << phong.ka << "\n";
		//cout << "ks: " << phong.ks << "\n";
		//cout << "kd: " << phong.kd << "\n";
		//
		//cout << "eye: " << eye << "\n";
		//cout << "l: " << eye << "\n";
		//cout << "cd: " << eye << "\n";
		//cout << "h: " << eye << "\n";
		//cout << "cs: " << eye << "\n";

		color += (light -> intensity) * (cd + cs);

	}

	// CLAMP THE COLOR
	//clamper(color);
	color *= 255.0f;


	return color;
}

vec3 Scene::reflectRay(const Hit& hit, int refLimit, int refs, const vec3& incidence) {

	vec3 color = { 0,0,0 };

	if (refs >= refLimit) { // out of reflections
		//if (hit.reflect) { // hit is reflective so it has no color of its own
		//	return color;
		//}
		//else { // hit is phong so return that color instead
		//	return shadeReflect(hit.x, hit.n, hit.phong, -incidence); // incidenece here should be the previous rays dir, then negated
		//}
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
		float minT = INT_MAX;
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
		} else if (reflectHits[minIdx].reflect) { // no phong found, meaning it reflected!
			return color + reflectRay(reflectHits[minIdx], refLimit, refs + 1, dir);
		}
		else { // phong found, return base color + phong color AND STOP REFLECTING
			return color + shadeReflect(reflectHits[minIdx].x, reflectHits[minIdx].n, reflectHits[minIdx].phong, -dir);
		}

		//return shadeReflect(reflectHits[minIdx].x, reflectHits[minIdx].n, reflectHits[minIdx].phong, -dir); // return the base color + the reflected color
	}

	return color; // base case of just no output 

	/*vec3 color = { 0,0,0 }; // base color of nothing
	
	vec3 dir = normalize(glm::reflect(incidence, normalize(hit.n))); // dir = the reflection vector // MAKE SURE HIT.N IS NORMALIZED!!!!!!
	vec3 pos = hit.x + (dir * 0.05f); // position = hit spot + epsilon shift

	vector<vec3> ray = { pos,dir };

	vector<Hit> reflectHits;


	for (auto& shape : shapes) { // raycast for every shape in scene
		shape->raycast(ray, reflectHits);
	}

	if (!reflectHits.empty()) { // RECURSIVE CASE
		int minIdx;
			float minT = INT_MAX;
			minIdx = -1;

			for (int i = 0; i < reflectHits.size(); i++) {
				if (reflectHits[i].t < minT && reflectHits[i].t > 0) { // make sure .t is greater than 0 !!!
					minT = reflectHits[i].t;
					minIdx = i;
				}
			}

			if (minIdx == -1 || reflectHits[minIdx].reflect) { // no phong found :(
				return color;
			}

			return shadeReflect(reflectHits[minIdx].x, reflectHits[minIdx].n, reflectHits[minIdx].phong, -dir ); // return the base color + the reflected color
	}
	return color;
	*/
	/*

	// base case: return black since were out of reflections

	if (!hit.reflect) { // phong found, stop reflecting and return its color
		return color + shadeReflect(hit.x, hit.n, hit.phong, eye);
		//return color + shade(hit.x, hit.n, hit.phong);
	}
	else if (refs >= refLimit) {
		return color;
	}

	// recursive case: while hit is reflective AND refs is less than refLimit

	// new ray's direction is the current hits normal?

	float reflectEpsilon = 0.1f; // reduce self-reflection

	vec3 dir = incidence - (2.0f * hit.n * dot(incidence, hit.n));
	vec3 pos = hit.x + dir * reflectEpsilon;

	vector<vec3> ray = { pos,dir };

	vector<Hit> reflectHits;

	for (auto& shape : shapes) { // raycast for every shape in scene
		shape->raycast(ray, reflectHits);
	}

	if (!reflectHits.empty()) { // RECURSIVE CASE
		int minIdx;
		if (refs + 1 == refLimit) { // cant reflect again, look for a phong?
			float minT = INT_MAX;
			minIdx = -1;

			for (int i = 0; i < reflectHits.size(); i++) {
				if (reflectHits[i].t < minT && !reflectHits[i].reflect) {
					minT = reflectHits[i].t;
					minIdx = i;
				}
			}

			if (minIdx == -1) { // no phong found :(
				return color;
			}
		}
		else {
			minIdx = nearestHit(reflectHits);
		}

		return color + reflectRay(reflectHits[minIdx], refLimit, refs + 1, dir , dir); // return the base color + the reflected color
	}
	else { // if the reflection doesnt hit anything else then end
		return color;
	}*/
}

vec3 Scene::shadeReflect(const vec3& pos, const vec3& norm, const Phong& phong, vec3& eye) {
	// assume pos and norm are already in cam space?
	vec3 color = phong.ka;
	vec3 n = normalize(norm);

	clamper(n, -1, 1); // NORMALS SHOULD BE CLAMPED WITH [-1 TO 1] !!!

	vector<Hit> shadowHits; // put here
	vec3 dir;
	int idx;
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

		//cout << "ka: " << phong.ka << "\n";
		//cout << "ks: " << phong.ks << "\n";
		//cout << "kd: " << phong.kd << "\n";
		//
		//cout << "eye: " << eye << "\n";
		//cout << "l: " << eye << "\n";
		//cout << "cd: " << eye << "\n";
		//cout << "h: " << eye << "\n";
		//cout << "cs: " << eye << "\n";

		color += (light->intensity) * (cd + cs);

	}

	// CLAMP THE COLOR
	//clamper(color);
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