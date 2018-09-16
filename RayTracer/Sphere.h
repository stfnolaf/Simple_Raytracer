#pragma once

#ifndef _SPHERE_h
#define _SPHERE_h

#include "math.h"
#include "Object.h"
#include "Vect.h"
#include "Color.h"

class Sphere : public Object {

	Vect pos;
	double radius;
	Color color;

public:

	Sphere();

	Sphere(Vect, double, Color);

	//method functions
	Vect getSpherePos();
	double getSphereRadius();
	virtual Color getColor();

	virtual Vect getNormalAt(Vect point);

	virtual double findIntersection(Ray ray);

};
#endif