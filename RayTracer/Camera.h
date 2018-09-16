#pragma once
#pragma once

#ifndef _CAMERA_H
#define _CAMERA_H

#include "glm/glm.hpp"

class Camera {

	glm::vec3 pos, dir, right, up;

public:

	Camera();

	Camera(glm::vec3, glm::vec3, glm::vec3, glm::vec3);

	//method functions
	glm::vec3 getCameraPos() { return pos; }
	glm::vec3 getCameraDir() { return dir; }
	glm::vec3 getCameraRight() { return right; }
	glm::vec3 getCameraUp() { return up; }

};

Camera::Camera() {
	pos = glm::vec3(0.0f, 0.0f, 0.0f);
	dir = glm::vec3(0.0f, 0.0f, 1.0f);
	right = glm::vec3(0.0f, 0.0f, 0.0f);
	up = glm::vec3(0.0f, 0.0f, 0.0f);
}

Camera::Camera(glm::vec3 p, glm::vec3 d, glm::vec3 r, glm::vec3 u) {
	pos = p;
	dir = d;
	right = r;
	up = u;
}

#endif