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
	Vect getPlaneNormal() { return normal; }
	double getPlaneDist() { return dist; }
	virtual Color getColor() { return color; }

	virtual Vect getNormalAt(Vect point) {
		return normal;
	}

	virtual double findIntersection(Ray ray) {
		Vect ray_dir = ray.getRayDir();

		double a = ray_dir.dot(normal);

		if (a == 0) {
			return -1;
		}
		else {
			double b = normal.dot(ray.getRayOrigin().add((normal.negative()).multiply(dist)));
			return -1 * b / a;
		}
	}

};

Plane::Plane() {
	normal = Vect(1, 0, 0);
	dist = 0;
	color = Color(0.5, 0.5, 0.5, 0);
}

Plane::Plane(Vect n, double d, Color c) {
	normal = n;
	dist = d;
	color = c;
}

#endif