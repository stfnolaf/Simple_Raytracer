#pragma once

#ifndef _RAY_H
#define _RAY_H

#include "Vect.h"

class Ray {

	Vect origin, dir;

public:

	Ray();

	Ray(Vect, Vect);

	//method functions
	Vect getRayOrigin() { return origin; }
	Vect getRayDir() { return dir; }

};

Ray::Ray() {
	origin = Vect(0, 0, 0);
	dir = Vect(1, 0, 0);
}

Ray::Ray(Vect o, Vect d) {
	origin = o;
	dir = d;
}

#endif