#pragma once

#ifndef _OBJECT_h
#define _OBJECT_h

#include "Ray.h"
#include "Vect.h"
#include "Color.h"

class Object {
public:

	Object();

	//method functions
	virtual Color getColor() { return Color (0.0, 0.0, 0.0, 0.0); }

	virtual Vect getNormalAt(Vect pos) {
		return Vect(0, 0, 0);
	}

	virtual double findIntersection(Ray ray) {
		return 0;
	}

};

Object::Object() {}

#endif