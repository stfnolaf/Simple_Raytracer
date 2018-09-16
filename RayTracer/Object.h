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
	virtual Color getColor();

	virtual Vect getNormalAt(Vect pos);

	virtual double findIntersection(Ray ray);

};
#endif