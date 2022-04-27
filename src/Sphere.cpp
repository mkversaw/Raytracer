#include "Sphere.h"

Sphere::Sphere() {
	pos = { 0,0,0 };
	rotation = { 0,0,0 };
	scale = { 1,1,1 };
	radius = 1.0f;
}

Sphere::Sphere(const vec3& p = { 0,0,0 }, const vec3& s = { 1,1,1 }, const vec3& r = { 0,0,0 }, const float rad = 1.0f) {
	this->pos = p;
	this->rotation = r;
	this->scale = s;
	this->radius = rad;
}

void Sphere::raycast(const vector<vec3>& ray, vector<Hit>& hits) {

	////////// Task 4: Find scaled/translated sphere intersection(s)

	vec3 pPrime = invE * vec4(ray[0],1);
	vec3 vPrime = normalize( invE * vec4(ray[1],0) );

	float a = dot(vPrime, vPrime);
	float b = 2 * (dot(vPrime, pPrime));
	float c = (dot(pPrime, pPrime)) - 1;
	float d = pow(b, 2) - 4 * a * c;

	if (d > 0) {
		float tPrime1 = (-b - sqrt(d)) / (2 * a);
		float tPrime2 = (-b + sqrt(d)) / (2 * a);

		vec3 xPrime1 = pPrime + tPrime1 * vPrime;
		vec3 xPrime2 = pPrime + tPrime2 * vPrime;

		vec3 x1 = E * vec4(xPrime1,1);
		vec3 x2 = E * vec4(xPrime2,1);

		vec3 n1 = normalize(transpose(invE) * vec4(xPrime1,0));
		vec3 n2 = normalize(transpose(invE) * vec4(xPrime2,0));

		float t1 = length(x1 - ray[0]);
		float t2 = length(x2 - ray[0]);

		if (dot(ray[1], x1 - ray[0]) < 0) {
			t1 = -t1;
		}

		if (dot(ray[1], x2 - ray[0]) < 0) {
			t2 = -t2;
		}

		hits.push_back({ x1,n1,t1,phong });
		hits.push_back({ x2,n2,t2,phong });
	}


	//vec3 pc = ray[0] - pos;
	//float a = dot(ray[1], ray[1]);
	//float b = 2 * (dot(ray[1], pc));
	//float c2 = dot(pc, pc) - pow(radius, 2);
	//float d = pow(b, 2) - 4 * a * c2;
	//
	//if (d > 0) {
	//	float t1 = (-b - sqrt(d)) / (2 * a);
	//	float t2 = (-b + sqrt(d)) / (2 * a);
	//
	//	vec3 x1 = ray[0] + t1 * ray[1];
	//	vec3 x2 = ray[0] + t2 * ray[1];
	//
	//	vec3 n1 = (x1 - pos) / radius;
	//	vec3 n2 = (x2 - pos) / radius;
	//
	//	hits.push_back({ x1,n1,t1,phong }); 
	//	hits.push_back({ x2,n2,t2,phong });
	//}

}

void Sphere::shadowCast(const vector<vec3>& ray, vector<Hit>& hits, float maxDist) {
	////////// Task 4: Find scaled/translated sphere intersection(s)

	vec3 pPrime = invE * vec4(ray[0], 1);
	vec3 vPrime = normalize(invE * vec4(ray[1], 0));

	float a = dot(vPrime, vPrime);
	float b = 2 * (dot(vPrime, pPrime));
	float c = (dot(pPrime, pPrime)) - 1;
	float d = pow(b, 2) - 4 * a * c;

	if (d > 0) {
		float tPrime1 = (-b - sqrt(d)) / (2 * a);
		float tPrime2 = (-b + sqrt(d)) / (2 * a);

		vec3 xPrime1 = pPrime + tPrime1 * vPrime;
		vec3 xPrime2 = pPrime + tPrime2 * vPrime;

		vec3 x1 = E * vec4(xPrime1, 1);
		vec3 x2 = E * vec4(xPrime2, 1);

		vec3 n1 = normalize(transpose(invE) * vec4(xPrime1, 0));
		vec3 n2 = normalize(transpose(invE) * vec4(xPrime2, 0));

		float t1 = length(x1 - ray[0]);
		float t2 = length(x2 - ray[0]);

		if (dot(ray[1], x1 - ray[0]) < 0) {
			t1 = -t1;
		}

		if (dot(ray[1], x2 - ray[0]) < 0) {
			t2 = -t2;
		}

		if (t1 > 0 && t1 < maxDist) {
			hits.push_back({ x1,n1,t1,phong });
		}

		if (t2 > 0 && t2 < maxDist) {
			hits.push_back({ x2,n2,t2,phong });
		}
	}

	//vec3 pc = ray[0] - pos;
	//float a = dot(ray[1], ray[1]);
	//float b = 2 * (dot(ray[1], pc));
	//float c2 = dot(pc, pc) - pow(radius, 2);
	//float d = pow(b, 2) - 4 * a * c2;
	//
	//if (d > 0) {
	//	float t1 = (-b - sqrt(d)) / (2 * a);
	//	float t2 = (-b + sqrt(d)) / (2 * a);
	//
	//
	//	if (t1 > 0 && t1 < maxDist) {
	//		vec3 x1 = ray[0] + t1 * ray[1];
	//		vec3 n1 = (x1 - pos) / radius;
	//		hits.push_back({ x1,n1,t1,phong });
	//	}
	//
	//	if (t2 > 0 && t2 < maxDist) {
	//		vec3 x2 = ray[0] + t2 * ray[1];
	//		vec3 n2 = (x2 - pos) / radius;
	//		hits.push_back({ x2,n2,t2,phong });
	//	}
	//}
}

void Sphere::setE() {
	auto M = make_shared<MatrixStack>();
	M->translate(pos);

	M->rotate(rotation.x, 1, 0, 0); // handle rotation for x,y,z
	M->rotate(rotation.y, 0, 1, 0);
	M->rotate(rotation.z, 0, 0, 1);

	M->scale(scale);

	this->E = M->topMatrix();
	this->invE = inverse(E);
}