#pragma once

#ifndef _RAY_H
#define _RAY_H

#include "glm/glm.hpp"

class Ray {

	glm::vec3 origin, dir;

public:

	Ray();

	Ray(glm::vec3, glm::vec3);

	//method functions
	glm::vec3 getRayOrigin() { return origin; }
	glm::vec3 getRayDir() { return dir; }

};

Ray::Ray() {
	origin = glm::vec3(0.0f, 0.0f, 0.0f);
	dir = glm::vec3(1.0f, 0.0f, 0.0f);
}

Ray::Ray(glm::vec3 o, glm::vec3 d) {
	origin = o;
	dir = d;
}

#endif