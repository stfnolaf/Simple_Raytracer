#pragma once

#ifndef _PLANE_H
#define _PLANE_H

#include "math.h"
#include "Object.h"
#include "Vect.h"
#include "Color.h"

class Plane : public Object {

	Vect normal;
	double dist;
	Color color;

public:

	Plane();

	Plane(Vect, double, Color);

	//method functions
	Vect getNormal();
	double getPlaneDist();
	virtual Color getColor();

	virtual Vect getNormalAt(Vect point);

	virtual double findIntersection(Ray ray);

};
#endif