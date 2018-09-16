#pragma once

#ifndef _LIGHT_h
#define _LIGHT_h

#include "Source.h"
#include "glm/glm.hpp"
#include "Color.h"

class Light : public Source {

	glm::vec3 pos;
	Color color;

public:

	Light();

	Light(glm::vec3, Color);

	//method functions
	virtual glm::vec3 getLightPos() { return pos; }
	virtual Color getLightColor() { return color; }

};

Light::Light() {
	pos = glm::vec3(0.0f, 0.0f, 0.0f);
	color = Color(1, 1, 1, 0);
}

Light::Light(glm::vec3 p, Color c) {
	pos = p;
	color = c;
}

#endif