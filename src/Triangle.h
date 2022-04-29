#pragma once
#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Shape.h"
#include <math.h>

#define EPSILON 0.000001
#define CROSS(dest,v1,v2) \
          dest[0]=v1[1]*v2[2]-v1[2]*v2[1]; \
          dest[1]=v1[2]*v2[0]-v1[0]*v2[2]; \
          dest[2]=v1[0]*v2[1]-v1[1]*v2[0];
#define DOT(v1,v2) (v1[0]*v2[0]+v1[1]*v2[1]+v1[2]*v2[2])
#define SUB(dest,v1,v2) \
          dest[0]=v1[0]-v2[0]; \
          dest[1]=v1[1]-v2[1]; \
          dest[2]=v1[2]-v2[2];


struct Triangle : Shape {
	
    float vert0[3];
    float vert1[3];
    float vert2[3];
    
    vec3 n1;
    vec3 n2;
    vec3 n3;

 

	Triangle(vec3& iv1, vec3& iv2, vec3& iv3, vec3& in1, vec3& in2, vec3& in3) : n1(in1), n2(in2), n3(in3) {
        vert0[0] = iv1.x;
        vert0[1] = iv1.y;
        vert0[2] = iv1.z;

        vert1[0] = iv2.x;
        vert1[1] = iv2.y;
        vert1[2] = iv2.z;

        vert2[0] = iv3.x;
        vert2[1] = iv3.y;
        vert2[2] = iv3.z;

	}

    void raycast(const vector<vec3>& ray, std::vector<Hit>& hits) {
        // return val is 1 if there is a hit
        // orig is ray origin, dir is ray direction
        float orig[3] = {ray[0].x,ray[0].y,ray[0].z};
        float dir[3] = {ray[1].x,ray[1].y,ray[1].z};
        float t, u, v, w;
        
        if (intersect_triangle(orig, dir, t, u, v) == 1) {
            if (t > 0) {
                // make a hit

                w = 1 - u - v;

                float norm1 = v * n1.x + w * n2.x + u * n3.x;
                float norm2 = v * n1.y + w * n2.y + u * n3.y;
                float norm3 = v * n1.z + w * n2.z + u * n3.z;
                
                vec3 x = vec3(orig[0],orig[1],orig[2]) + t * vec3(dir[0],dir[1],dir[2]);
                   
                hits.push_back({x,vec3(norm1,norm2,norm3),t,phong,false});
            }
        }

    }

    bool shadowCast(const vector<vec3>& ray, float maxDist) {
        return false;
    }

    void setE() {

    }

    int intersect_triangle(float orig[3], float dir[3], float& t, float& u, float& v)
    {
        float edge1[3], edge2[3], tvec[3], pvec[3], qvec[3];
        float det, inv_det;

        /* find vectors for two edges sharing vert0 */
        SUB(edge1, vert1, vert0);
        SUB(edge2, vert2, vert0);

        /* begin calculating determinant - also used to calculate U parameter */
        CROSS(pvec, dir, edge2);

        /* if determinant is near zero, ray lies in plane of triangle */
        det = DOT(edge1, pvec);

        if (det > -EPSILON && det < EPSILON)
            return 0;
        inv_det = 1.0 / det;

        /* calculate distance from vert0 to ray origin */
        SUB(tvec, orig, vert0);

        /* calculate U parameter and test bounds */
        u = DOT(tvec, pvec) * inv_det;
        if (u < 0.0 || u > 1.0)
            return 0;

        /* prepare to test V parameter */
        CROSS(qvec, tvec, edge1);

        /* calculate V parameter and test bounds */
        v = DOT(dir, qvec) * inv_det;
        if (v < 0.0 || u + v > 1.0)
            return 0;

        /* calculate t, ray intersects triangle */
        t = DOT(edge2, qvec) * inv_det;

        return 1;
    }
	
};




#endif