#pragma once

#ifndef _SPHERE_h
#define _SPHERE_h

#include "math.h"
#include "Object.h"
#include "glm/glm.hpp"
#include "Color.h"

class Sphere : public Object {

	glm::vec3 pos;
	float radius;
	Color color;

public:

	Sphere();

	Sphere(glm::vec3, float, Color);

	//method functions
	glm::vec3 getSpherePos() { return pos; }
	float getSphereRadius() { return radius; }
	virtual Color getColor() { return color; }

	virtual glm::vec3 getNormalAt(glm::vec3 point) {
		// normal always points away from center
		glm::vec3 normalVector = glm::normalize(point - pos);
		return normalVector;
	}

	virtual float findIntersection(Ray ray) {
		glm::vec3 rayOrigin = ray.getRayOrigin();
		float rayOriginX = rayOrigin.x;
		float rayOriginY = rayOrigin.y;
		float rayOriginZ = rayOrigin.z;

		glm::vec3 rayDir = ray.getRayDir();
		float rayDirX = rayDir.x;
		float rayDirY = rayDir.y;
		float rayDirZ = rayDir.z;

		glm::vec3 spherePos = pos;
		float spherePosX = spherePos.x;
		float spherePosY = spherePos.y;
		float spherePosZ = spherePos.z;

		float a = 1.0f;
		float b = (2.0f * (rayOriginX - spherePosX)*rayDirX) + (2.0f * (rayOriginY - spherePosY)*rayDirY) + (2.0f * (rayOriginZ - spherePosZ)*rayDirZ);
		float c = pow(rayOriginX - spherePosX, 2.0f) + pow(rayOriginY - spherePosY, 2.0f) + pow(rayOriginZ - spherePosZ, 2.0f) - (radius*radius);

		float discriminant = b * b - 4 * c;

		if (discriminant > 0.0f) {
			float root1 = ((-1 * b - sqrt(discriminant)) / 2.0f) /*- 0.000001f*/;
			
			if (root1 > 0.0f) {
				return root1;
			}
			else {
				float root2 = ((sqrt(discriminant) - b) / 2.0f) /*- 0.000001f*/;
				return root2;
			}
		}
		else {
			return -1.0f;
		}

	}

};

Sphere::Sphere() {
	pos = glm::vec3(0.0f, 0.0f, 0.0f);
	radius = 1.0;
	color = Color(0.5f, 0.5f, 0.5f, 0.0f);
}

Sphere::Sphere(glm::vec3 p, float r, Color c) {
	pos = p;
	radius = r;
	color = c;
}

#endif