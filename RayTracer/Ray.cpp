#include "pch.h"
#include "Ray.h"

Ray::Ray() {
	origin = Vect(0, 0, 0);
	dir = Vect(1, 0, 0);
}

Ray::Ray(Vect o, Vect d) {
	origin = o;
	dir = d;
}

Vect Ray::getRayOrigin() {
	return origin;
}

Vect Ray::getRayDir() {
	return dir;
}