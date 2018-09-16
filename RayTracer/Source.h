#pragma once

#ifndef _SOURCE_H
#define _SOURCE_H

#include "glm/glm.hpp"
#include "Color.h"

class Source {

public:
	Source();
	
	virtual glm::vec3 getLightPos() { return glm::vec3(0.0f, 0.0f, 0.0f); }

	virtual Color getLightColor() { return Color(1.0f, 1.0f, 1.0f, 0.0f); }

};

Source::Source() {}

#endif
