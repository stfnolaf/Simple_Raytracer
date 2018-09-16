#pragma once

#ifndef _OBJECT_h
#define _OBJECT_h

#include "Ray.h"
#include "glm/glm.hpp"
#include "Color.h"

class Object {
public:

	Object();

	//method functions
	virtual Color getColor() { return Color (0.0, 0.0, 0.0, 0.0); }

	virtual glm::vec3 getNormalAt(glm::vec3 pos) {
		return glm::vec3(0.0f, 0.0f, 0.0f);
	}

	virtual float findIntersection(Ray ray) {
		return 0.0f;
	}

};

Object::Object() {}

#endif