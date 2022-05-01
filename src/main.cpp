#include <iostream>
#include <string>

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

#include "Scene.h"
#include <glm/gtc/type_ptr.hpp>

// This allows you to skip the `std::` in front of C++ standard library
// functions. You can also say `using std::cout` to be more selective.
// You should never do this in a header file.
using namespace std;

int sceneSelect,width, height;

shared_ptr<Scene> scene;

Phong cyan = Phong(vec3(0.0, 1.0, 1.0), vec3(0.5, 1.0, 1.0), vec3(0.1, 0.1, 0.1), 100.0f);
Phong magenta = Phong(vec3(1.0, 0.0, 1.0), vec3(1.0, 0.5, 1.0), vec3(0.1, 0.1, 0.1), 100.0f);

float dist(vec3& center,vec3& testPoint) {
	return sqrt(pow(center.x - testPoint.x, 2.0f) + pow(center.y - testPoint.y, 2.0f) + pow(center.z - testPoint.z, 2.0f));
}

int main(int argc, char **argv)
{
	if (argc < 4) {
		cout << "Usage: A6 scene width filename/path\n";
		return 0;
	}

	sceneSelect = atoi(argv[1]);

	cout << "Selected scene " << sceneSelect << ", creating and rendering now\n";

	width = atoi(argv[2]);
	height = width;

	string filename(argv[3]);

	scene = make_shared<Scene>(width,height);

	if (sceneSelect == 1 || sceneSelect == 2) {
		shared_ptr<Light> light = make_shared<Light>(vec3(-2.0f, 1.0f, 1.0f),1.0f);
		scene->lights.push_back(light);

		shared_ptr<Sphere> redBall = make_shared<Sphere>(vec3(-0.5f, -1.0f, 1.0f), vec3(1, 1, 1), vec3(0, 0, 0), 1.0f); // pos , scale , rotation , RADIUS
		Phong red = Phong(vec3(1.0, 0.0, 0.0), vec3(1.0, 1.0, 0.5), vec3(0.1, 0.1, 0.1), 100.0f);
		redBall->phong = red;
		scene->shapes.push_back(redBall);

		shared_ptr<Sphere> greenBall = make_shared<Sphere>(vec3(0.5f, -1.0f, -1.0f), vec3(1, 1, 1), vec3(0, 0, 0), 1.0f); // pos , scale , rotation , RADIUS
		Phong green = Phong(vec3(0.0, 1.0, 0.0), vec3(1.0, 1.0, 0.5), vec3(0.1, 0.1, 0.1), 100.0f);
		greenBall->phong = green;
		scene->shapes.push_back(greenBall);

		shared_ptr<Sphere> blueBall = make_shared<Sphere>(vec3(0.0f, 1.0f, 0.0f), vec3(1, 1, 1), vec3(0, 0, 0), 1.0f); // pos , scale , rotation , RADIUS
		Phong blue = Phong(vec3(0.0, 0.0, 1.0), vec3(1.0, 1.0, 0.5), vec3(0.1, 0.1, 0.1), 100.0f);
		blueBall->phong = blue;
		scene->shapes.push_back(blueBall);
	}
	else if (sceneSelect == 3) {
		shared_ptr<Light> light1 = make_shared<Light>(vec3(1.0f, 2.0f, 2.0f),0.5f);
		scene->lights.push_back(light1);

		shared_ptr<Light> light2 = make_shared<Light>(vec3(-1.0f, 2.0f, -1.0f), 0.5f);
		scene->lights.push_back(light2);


		shared_ptr<Sphere> greenBall = make_shared<Sphere>(vec3(-0.5f, 0.0f, -0.5f), vec3(1, 1, 1), vec3(0, 0, 0), 1.0f); // pos , scale , rotation , RADIUS
		Phong green = Phong(vec3(0.0, 1.0, 0.0), vec3(1.0, 1.0, 0.5), vec3(0.1, 0.1, 0.1), 100.0f);
		greenBall->phong = green;
		scene->shapes.push_back(greenBall);

		shared_ptr<Sphere> redEllipsoid = make_shared<Sphere>(vec3(0.5f, 0.0f, 0.5f), vec3(0.5, 0.6, 0.2), vec3(0, 0, 0), 1.0f); // pos , scale , rotation , RADIUS
		Phong red = Phong(vec3(1.0, 0.0, 0.0), vec3(1.0, 1.0, 0.5), vec3(0.1, 0.1, 0.1), 100.0f);
		redEllipsoid->phong = red;
		scene->shapes.push_back(redEllipsoid);

		shared_ptr<Plane> plane = make_shared<Plane>(vec3(0, -1.0, 0), vec3(1, 1, 1), vec3(glm::pi<float>() / 2, 0, 0)); // pos , scale , rotation
		plane->phong = Phong(vec3(1.0,1.0,1.0),vec3(0.0,0.0,0.0),vec3(0.1,0.1,0.1),0.0f);

		scene->shapes.push_back(plane);
	}
	else if (sceneSelect == 4 || sceneSelect == 5) {
		shared_ptr<Light> light1 = make_shared<Light>(vec3(-1.0f, 2.0f, 1.0f), 0.5f);
		scene->lights.push_back(light1);

		shared_ptr<Light> light2 = make_shared<Light>(vec3(0.5f, -0.5f, 0.0f), 0.5f);
		scene->lights.push_back(light2);

		shared_ptr<Sphere> redBall = make_shared<Sphere>(vec3(0.5f, -0.7f, 0.5f), vec3(0.3, 0.3, 0.3), vec3(0, 0, 0), 1.0f); // pos , scale , rotation , RADIUS
		Phong red = Phong(vec3(1.0, 0.0, 0.0), vec3(1.0, 1.0, 0.5), vec3(0.1, 0.1, 0.1), 100.0f);
		redBall->phong = red;
		scene->shapes.push_back(redBall);

		shared_ptr<Sphere> blueBall = make_shared<Sphere>(vec3(1.0f, -0.7f, 0.0f), vec3(0.3, 0.3, 0.3), vec3(0, 0, 0), 1.0f); // pos , scale , rotation , RADIUS
		Phong blue = Phong(vec3(0.0, 0.0, 1.0), vec3(1.0, 1.0, 0.5), vec3(0.1, 0.1, 0.1), 100.0f);
		blueBall->phong = blue;
		scene->shapes.push_back(blueBall);

		shared_ptr<Plane> floor = make_shared<Plane>(vec3(0, -1.0, 0), vec3(1, 1, 1), vec3(glm::pi<float>() / 2, 0, 0)); // pos , scale , rotation
		floor->phong = Phong(vec3(1.0, 1.0, 1.0), vec3(0.0, 0.0, 0.0), vec3(0.1, 0.1, 0.1), 0.0f);
		scene->shapes.push_back(floor);

		shared_ptr<Plane> backWall = make_shared<Plane>(vec3(0, 0.0, -3.0), vec3(1, 1, 1), vec3(0, glm::pi<float>(), 0)); // pos , scale , rotation
		backWall->phong = Phong(vec3(1.0, 1.0, 1.0), vec3(0.0, 0.0, 0.0), vec3(0.1, 0.1, 0.1), 0.0f);
		backWall->normal = { 0,0,1 };
		scene->shapes.push_back(backWall);

		shared_ptr<Sphere> reflectiveBall1 = make_shared<Sphere>(vec3(-0.5f, 0.0f, -0.5f), vec3(1.0, 1.0, 1.0), vec3(0, 0, 0), 1.0f); // pos , scale , rotation , RADIUS
		reflectiveBall1->reflective = true;
		scene->shapes.push_back(reflectiveBall1);

		shared_ptr<Sphere> reflectiveBall2 = make_shared<Sphere>(vec3(1.5f, 0.0f, -1.5f), vec3(1.0, 1.0, 1.0), vec3(0, 0, 0), 1.0f); // pos , scale , rotation , RADIUS
		reflectiveBall2->reflective = true;
		scene->shapes.push_back(reflectiveBall2);
	}
	else if (sceneSelect == 6) {



		string meshName = "../resources/bunny.obj";
		// Load geometry
		vector<float> posBuf; // list of vertex positions
		vector<float> norBuf; // list of vertex normals
		vector<float> texBuf; // list of vertex texture coords
		tinyobj::attrib_t attrib;
		std::vector<tinyobj::shape_t> shapesVec;
		std::vector<tinyobj::material_t> materials;
		string errStr;
		bool rc = tinyobj::LoadObj(&attrib, &shapesVec, &materials, &errStr, meshName.c_str());
		if (!rc) {
			cerr << errStr << endl;
		}
		else {
			for (size_t s = 0; s < shapesVec.size(); s++) {
				// Loop over faces (polygons)
				size_t index_offset = 0;
				for (size_t f = 0; f < shapesVec[s].mesh.num_face_vertices.size(); f++) {
					size_t fv = shapesVec[s].mesh.num_face_vertices[f];
					// Loop over vertices in the face.
					for (size_t v = 0; v < fv; v++) {
						// access to vertex
						tinyobj::index_t idx = shapesVec[s].mesh.indices[index_offset + v];
						posBuf.push_back(attrib.vertices[3 * idx.vertex_index + 0]);
						posBuf.push_back(attrib.vertices[3 * idx.vertex_index + 1]);
						posBuf.push_back(attrib.vertices[3 * idx.vertex_index + 2]);

						if (!attrib.normals.empty()) {
							norBuf.push_back(attrib.normals[3 * idx.normal_index + 0]);
							norBuf.push_back(attrib.normals[3 * idx.normal_index + 1]);
							norBuf.push_back(attrib.normals[3 * idx.normal_index + 2]);
						}
						if (!attrib.texcoords.empty()) {
							texBuf.push_back(attrib.texcoords[2 * idx.texcoord_index + 0]);
							texBuf.push_back(attrib.texcoords[2 * idx.texcoord_index + 1]);
						}
					}
					index_offset += fv;
					//shapesVec[s].mesh.material_ids[f];  // per-face material (IGNORE)
				}
			}
		}

		if (posBuf.size() < 9) {
			std::cout << "not enough vertices for a triangle!";
			return 0;
		}

		float meshRadius = -1;
		vec3 meshPosAvg = { 0,0,0 };

		for (int i = 0; i < posBuf.size(); i += 3) {
			meshPosAvg.x += posBuf[i];
			meshPosAvg.y += posBuf[i + 1];
			meshPosAvg.z += posBuf[i + 2];
		}
		meshPosAvg /= (posBuf.size() / 3); // centroid of the mesh

		Phong blue = Phong(vec3(0.0, 0.0, 1.0), vec3(1.0, 1.0, 0.5), vec3(0.1, 0.1, 0.1), 100.0f);
		shared_ptr<Light> light1 = make_shared<Light>(vec3(-1.0f, 1.0f, 1.0f), 1.0f);
		scene->lights.push_back(light1);

		auto M = make_shared<MatrixStack>();
		M->loadIdentity();
		glm::mat4 identity = M->topMatrix();

		for (int i = 0; i < posBuf.size(); i += 9) { // 9 per triangle

			vec3 v1 = { posBuf[i], posBuf[i + 1], posBuf[i + 2] };
			vec3 v2 = { posBuf[i + 3], posBuf[i + 4], posBuf[i + 5] };
			vec3 v3 = { posBuf[i + 6], posBuf[i + 7], posBuf[i + 8] };

			meshRadius = max(meshRadius,dist(meshPosAvg, v1));
			meshRadius = max(meshRadius,dist(meshPosAvg, v2));
			meshRadius = max(meshRadius,dist(meshPosAvg, v3));

			vec3 n1 = { norBuf[i], norBuf[i + 1], norBuf[i + 2] };
			vec3 n2 = { norBuf[i + 3], norBuf[i + 4], norBuf[i + 5] };
			vec3 n3 = { norBuf[i + 6], norBuf[i + 7], norBuf[i + 8] };

			shared_ptr<Triangle> tri = make_shared<Triangle>(v1,v2,v3,n1,n2,n3,identity); // vertices , normals for those verts, and the trans matrix
			tri->phong = blue;
			scene->shapes.push_back(tri);
		}

		scene->isMesh = true; // very important do not forget!!!

		scene->boundingSphere = make_shared<Sphere>(meshPosAvg, vec3(meshRadius, meshRadius, meshRadius), vec3(0, 0, 0), 1.0f);
		scene->boundingSphere->setE();

	}
	else if (sceneSelect == 7) {
		auto M = make_shared<MatrixStack>();
		M->translate(0.3f, -1.5f, 0.0f);
		constexpr float deg = 20.0f * (glm::pi<float>() / 180.0f); // 20 degrees in radians
		M->rotate(deg, vec3(1, 0, 0));
		M->scale(1.5f);
		glm::mat4 modelTrans = M->topMatrix();

		string meshName = "../resources/bunny.obj";
		// Load geometry
		vector<float> posBuf; // list of vertex positions
		vector<float> norBuf; // list of vertex normals
		vector<float> texBuf; // list of vertex texture coords
		tinyobj::attrib_t attrib;
		std::vector<tinyobj::shape_t> shapesVec;
		std::vector<tinyobj::material_t> materials;
		string errStr;
		bool rc = tinyobj::LoadObj(&attrib, &shapesVec, &materials, &errStr, meshName.c_str());
		if (!rc) {
			cerr << errStr << endl;
		}
		else {
			for (size_t s = 0; s < shapesVec.size(); s++) {
				// Loop over faces (polygons)
				size_t index_offset = 0;
				for (size_t f = 0; f < shapesVec[s].mesh.num_face_vertices.size(); f++) {
					size_t fv = shapesVec[s].mesh.num_face_vertices[f];
					// Loop over vertices in the face.
					for (size_t v = 0; v < fv; v++) {
						// access to vertex
						tinyobj::index_t idx = shapesVec[s].mesh.indices[index_offset + v];
						posBuf.push_back(attrib.vertices[3 * idx.vertex_index + 0]);
						posBuf.push_back(attrib.vertices[3 * idx.vertex_index + 1]);
						posBuf.push_back(attrib.vertices[3 * idx.vertex_index + 2]);
						if (!attrib.normals.empty()) {
							norBuf.push_back(attrib.normals[3 * idx.normal_index + 0]);
							norBuf.push_back(attrib.normals[3 * idx.normal_index + 1]);
							norBuf.push_back(attrib.normals[3 * idx.normal_index + 2]);
						}
						if (!attrib.texcoords.empty()) {
							texBuf.push_back(attrib.texcoords[2 * idx.texcoord_index + 0]);
							texBuf.push_back(attrib.texcoords[2 * idx.texcoord_index + 1]);
						}
					}
					index_offset += fv;
					//shapesVec[s].mesh.material_ids[f]; // per-face material (IGNORE)
				}
			}
		}

		if (posBuf.size() < 9) {
			std::cout << "not enough vertices for a triangle!";
			return 0;
		}

		float meshRadius = -1;
		vec3 meshPosAvg = { 0,0,0 };

		for (int i = 0; i < posBuf.size(); i += 3) {
			meshPosAvg.x += posBuf[i];
			meshPosAvg.y += posBuf[i + 1];
			meshPosAvg.z += posBuf[i + 2];
		}
		meshPosAvg /= (posBuf.size() / 3); // centroid of the mesh

		Phong blue = Phong(vec3(0.0, 0.0, 1.0), vec3(1.0, 1.0, 0.5), vec3(0.1, 0.1, 0.1), 100.0f);
		shared_ptr<Light> light1 = make_shared<Light>(vec3(1.0f, 1.0f, 2.0f), 1.0f);
		scene->lights.push_back(light1);
		vec3 v1, v2, v3;
		vec3 n1, n2, n3;
		for (int i = 0; i < posBuf.size(); i += 9) { // 9 per triangle

			v1 = { posBuf[i], posBuf[i + 1], posBuf[i + 2] };
			v2 = { posBuf[i + 3], posBuf[i + 4], posBuf[i + 5] };
			v3 = { posBuf[i + 6], posBuf[i + 7], posBuf[i + 8] };

			meshRadius = max(meshRadius, dist(meshPosAvg, v1));
			meshRadius = max(meshRadius, dist(meshPosAvg, v2));
			meshRadius = max(meshRadius, dist(meshPosAvg, v3));

			n1 = { norBuf[i], norBuf[i + 1], norBuf[i + 2] };
			n2 = { norBuf[i + 3], norBuf[i + 4], norBuf[i + 5] };
			n3 = { norBuf[i + 6], norBuf[i + 7], norBuf[i + 8] };


			shared_ptr<Triangle> tri = make_shared<Triangle>(v1, v2, v3, n1, n2, n3, modelTrans); // vertices , normals for those verts, and the trans matrix
			tri->phong = blue;
			scene->shapes.push_back(tri);

		}
		scene->isMesh = true;

		scene->boundingSphere = make_shared<Sphere>(meshPosAvg, vec3(meshRadius, meshRadius, meshRadius), vec3(0, 0, 0), 1.0f);
		scene->boundingSphere->setE();

		std::shared_ptr<MatrixStack> MV = std::make_shared<MatrixStack>();
		MV->loadIdentity();
		MV->multMatrix(modelTrans);
		MV->multMatrix(scene->boundingSphere->E);
		scene->boundingSphere->E = MV->topMatrix();
		scene->boundingSphere->invE = inverse(MV->topMatrix());

		scene->init();
		scene->render();
	}
	else if (sceneSelect == 0) { // bonus 1 (blended reflection and phong)
		shared_ptr<Light> light1 = make_shared<Light>(vec3(-1.0f, 2.0f, 1.0f), 0.5f);
		scene->lights.push_back(light1);

		shared_ptr<Light> light2 = make_shared<Light>(vec3(0.5f, -0.5f, 0.0f), 0.5f);
		scene->lights.push_back(light2);

		shared_ptr<Sphere> redBall = make_shared<Sphere>(vec3(0.5f, -0.7f, 0.5f), vec3(0.3, 0.3, 0.3), vec3(0, 0, 0), 1.0f); // pos , scale , rotation , RADIUS
		Phong red = Phong(vec3(1.0, 0.0, 0.0), vec3(1.0, 1.0, 0.5), vec3(0.1, 0.1, 0.1), 100.0f);
		redBall->phong = red;
		scene->shapes.push_back(redBall);

		shared_ptr<Sphere> blueBall = make_shared<Sphere>(vec3(1.0f, -0.7f, 0.0f), vec3(0.3, 0.3, 0.3), vec3(0, 0, 0), 1.0f); // pos , scale , rotation , RADIUS
		Phong blue = Phong(vec3(0.0, 0.0, 1.0), vec3(1.0, 1.0, 0.5), vec3(0.1, 0.1, 0.1), 100.0f);
		blueBall->phong = blue;
		scene->shapes.push_back(blueBall);

		shared_ptr<Plane> floor = make_shared<Plane>(vec3(0, -1.0, 0), vec3(1, 1, 1), vec3(glm::pi<float>() / 2, 0, 0)); // pos , scale , rotation
		floor->phong = Phong(vec3(1.0, 1.0, 1.0), vec3(0.0, 0.0, 0.0), vec3(0.1, 0.1, 0.1), 0.0f);
		scene->shapes.push_back(floor);

		shared_ptr<Plane> backWall = make_shared<Plane>(vec3(0, 0.0, -3.0), vec3(1, 1, 1), vec3(0, glm::pi<float>(), 0)); // pos , scale , rotation
		backWall->phong = Phong(vec3(1.0, 1.0, 1.0), vec3(0.0, 0.0, 0.0), vec3(0.1, 0.1, 0.1), 0.0f);
		backWall->normal = { 0,0,1 };
		scene->shapes.push_back(backWall);

		shared_ptr<Sphere> reflectiveBall1 = make_shared<Sphere>(vec3(-0.5f, 0.0f, -0.5f), vec3(1.0, 1.0, 1.0), vec3(0, 0, 0), 1.0f); // pos , scale , rotation , RADIUS
		reflectiveBall1->reflective = true;
		reflectiveBall1->phong = cyan;
		scene->shapes.push_back(reflectiveBall1);

		shared_ptr<Sphere> reflectiveBall2 = make_shared<Sphere>(vec3(1.5f, 0.0f, -1.5f), vec3(1.0, 1.0, 1.0), vec3(0, 0, 0), 1.0f); // pos , scale , rotation , RADIUS
		reflectiveBall2->reflective = true;
		
		reflectiveBall2->phong = magenta;
		scene->shapes.push_back(reflectiveBall2);

		scene->reflectLimit = 2;
		scene->isBlend = true;
	}
	else if (sceneSelect == 9) { // bonus 2 (anti-aliasing)
		shared_ptr<Light> light = make_shared<Light>(vec3(-2.0f, 1.0f, 1.0f), 1.0f);
		scene->lights.push_back(light);

		shared_ptr<Sphere> redBall = make_shared<Sphere>(vec3(-0.5f, -1.0f, 1.0f), vec3(1, 1, 1), vec3(0, 0, 0), 1.0f); // pos , scale , rotation , RADIUS
		Phong red = Phong(vec3(1.0, 0.0, 0.0), vec3(1.0, 1.0, 0.5), vec3(0.1, 0.1, 0.1), 100.0f);
		redBall->phong = red;
		scene->shapes.push_back(redBall);

		shared_ptr<Sphere> greenBall = make_shared<Sphere>(vec3(0.5f, -1.0f, -1.0f), vec3(1, 1, 1), vec3(0, 0, 0), 1.0f); // pos , scale , rotation , RADIUS
		Phong green = Phong(vec3(0.0, 1.0, 0.0), vec3(1.0, 1.0, 0.5), vec3(0.1, 0.1, 0.1), 100.0f);
		greenBall->phong = green;
		scene->shapes.push_back(greenBall);

		shared_ptr<Sphere> blueBall = make_shared<Sphere>(vec3(0.0f, 1.0f, 0.0f), vec3(1, 1, 1), vec3(0, 0, 0), 1.0f); // pos , scale , rotation , RADIUS
		Phong blue = Phong(vec3(0.0, 0.0, 1.0), vec3(1.0, 1.0, 0.5), vec3(0.1, 0.1, 0.1), 100.0f);
		blueBall->phong = blue;
		scene->shapes.push_back(blueBall);

		scene->init();
		scene->renderAA4X(); // can swap this to renderAA16X() for better anti-aliasing
	}
	else if (sceneSelect == 10) { // NOT ACTUALLY ADDITIONAL BONUS, JUST COMBINING THE PREVIOUS TWO
		shared_ptr<Light> light1 = make_shared<Light>(vec3(-1.0f, 2.0f, 1.0f), 0.5f);
		scene->lights.push_back(light1);

		shared_ptr<Light> light2 = make_shared<Light>(vec3(0.5f, -0.5f, 0.0f), 0.5f);
		scene->lights.push_back(light2);

		shared_ptr<Sphere> redBall = make_shared<Sphere>(vec3(0.5f, -0.7f, 0.5f), vec3(0.3, 0.3, 0.3), vec3(0, 0, 0), 1.0f); // pos , scale , rotation , RADIUS
		Phong red = Phong(vec3(1.0, 0.0, 0.0), vec3(1.0, 1.0, 0.5), vec3(0.1, 0.1, 0.1), 100.0f);
		redBall->phong = red;
		scene->shapes.push_back(redBall);

		shared_ptr<Sphere> blueBall = make_shared<Sphere>(vec3(1.0f, -0.7f, 0.0f), vec3(0.3, 0.3, 0.3), vec3(0, 0, 0), 1.0f); // pos , scale , rotation , RADIUS
		Phong blue = Phong(vec3(0.0, 0.0, 1.0), vec3(1.0, 1.0, 0.5), vec3(0.1, 0.1, 0.1), 100.0f);
		blueBall->phong = blue;
		scene->shapes.push_back(blueBall);

		shared_ptr<Plane> floor = make_shared<Plane>(vec3(0, -1.0, 0), vec3(1, 1, 1), vec3(glm::pi<float>() / 2, 0, 0)); // pos , scale , rotation
		floor->phong = Phong(vec3(1.0, 1.0, 1.0), vec3(0.0, 0.0, 0.0), vec3(0.1, 0.1, 0.1), 0.0f);
		scene->shapes.push_back(floor);

		shared_ptr<Plane> backWall = make_shared<Plane>(vec3(0, 0.0, -3.0), vec3(1, 1, 1), vec3(0, glm::pi<float>(), 0)); // pos , scale , rotation
		backWall->phong = Phong(vec3(1.0, 1.0, 1.0), vec3(0.0, 0.0, 0.0), vec3(0.1, 0.1, 0.1), 0.0f);
		backWall->normal = { 0,0,1 };
		scene->shapes.push_back(backWall);

		shared_ptr<Sphere> reflectiveBall1 = make_shared<Sphere>(vec3(-0.5f, 0.0f, -0.5f), vec3(1.0, 1.0, 1.0), vec3(0, 0, 0), 1.0f); // pos , scale , rotation , RADIUS
		reflectiveBall1->reflective = true;
		reflectiveBall1->phong = cyan;
		scene->shapes.push_back(reflectiveBall1);

		shared_ptr<Sphere> reflectiveBall2 = make_shared<Sphere>(vec3(1.5f, 0.0f, -1.5f), vec3(1.0, 1.0, 1.0), vec3(0, 0, 0), 1.0f); // pos , scale , rotation , RADIUS
		reflectiveBall2->reflective = true;

		reflectiveBall2->phong = magenta;
		scene->shapes.push_back(reflectiveBall2);

		scene->reflectLimit = 3;
		scene->isBlend = true;

		scene->init();
		scene->renderAA16X(); // can swap this to renderAA16X() for better anti-aliasing
	}


	if (sceneSelect != 9 && sceneSelect != 7 && sceneSelect != 10) {
		scene->init();
		scene->render();
	}


	scene -> output(filename);

	return 0;
}
