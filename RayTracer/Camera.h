#pragma once
#pragma once

#ifndef _CAMERA_H
#define _CAMERA_H

#include "Vect.h"

class Camera {

	Vect pos, dir, right, up;

public:

	Camera();

	Camera(Vect, Vect, Vect, Vect);

	//method functions
	Vect getCameraPos() { return pos; }
	Vect getCameraDir() { return dir; }
	Vect getCameraRight() { return right; }
	Vect getCameraUp() { return up; }

};

Camera::Camera() {
	pos = Vect(0, 0, 0);
	dir = Vect(0, 0, 1);
	right = Vect(0, 0, 0);
	up = Vect(0, 0, 0);
}

Camera::Camera(Vect p, Vect d, Vect r, Vect u) {
	pos = p;
	dir = d;
	right = r;
	up = u;
}

#endif