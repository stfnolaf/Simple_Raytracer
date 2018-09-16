#pragma once
#ifndef _VECT_H
#define _VECT_H

#include "math.h"

class Vect {

	double x, y, z;

public:

	Vect();

	Vect(double, double, double);

	//functions
	double getX();
	double getY();
	double getZ();

	double magnitude();

	Vect normalize();

	Vect negative();

	double dot(Vect v);

	Vect cross(Vect v);

	Vect add(Vect v);

	Vect multiply(double scalar);

};
#endif