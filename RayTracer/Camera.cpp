#include "pch.h"
#include "Camera.h"

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

Vect Camera::getCameraPos() { return pos; }

Vect Camera::getCameraDir() { return dir; }

Vect Camera::getCameraRight() { return right; }

Vect Camera::getCameraUp() { return up; }