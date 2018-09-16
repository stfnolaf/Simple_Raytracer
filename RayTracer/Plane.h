#pragma once

#ifndef _PLANE_H
#define _PLANE_H

#include "math.h"
#include "Object.h"
#include "glm/glm.hpp"
#include "Color.h"

class Plane : public Object {

	glm::vec3 normal;
	float dist;
	Color color;

public:

	Plane();

	Plane(glm::vec3, float, Color);

	//method functions
	glm::vec3 getPlaneNormal() { return normal; }
	float getPlaneDist() { return dist; }
	virtual Color getColor() { return color; }

	virtual glm::vec3 getNormalAt(glm::vec3 point) {
		return normal;
	}

	virtual float findIntersection(Ray ray) {
		glm::vec3 ray_dir = ray.getRayDir();

		float a = glm::dot(ray_dir, normal);

		if (a == 0) {
			return -1.0f;
		}
		else {
			float b = glm::dot(normal, (ray.getRayOrigin() + (dist * -normal)));
			return -1.0f * b / a;
		}
	}

};

Plane::Plane() {
	normal = glm::vec3(1.0f, 0.0f, 0.0f);
	dist = 0.0f;
	color = Color(0.5, 0.5, 0.5, 0);
}

Plane::Plane(glm::vec3 n, float d, Color c) {
	normal = n;
	dist = d;
	color = c;
}

#endif