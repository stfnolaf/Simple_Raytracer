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
	Vect getSpherePos() { return pos; }
	double getSphereRadius() { return radius; }
	virtual Color getColor() { return color; }

	virtual Vect getNormalAt(Vect point) {
		// normal always points away from center
		Vect normalVector = point.add(pos.negative()).normalize();
		return normalVector;
	}

	virtual double findIntersection(Ray ray) {
		Vect rayOrigin = ray.getRayOrigin();
		double rayOriginX = rayOrigin.getX();
		double rayOriginY = rayOrigin.getY();
		double rayOriginZ = rayOrigin.getZ();

		Vect rayDir = ray.getRayDir();
		double rayDirX = rayDir.getX();
		double rayDirY = rayDir.getY();
		double rayDirZ = rayDir.getZ();

		Vect spherePos = pos;
		double spherePosX = spherePos.getX();
		double spherePosY = spherePos.getY();
		double spherePosZ = spherePos.getZ();

		double a = 1;
		double b = (2 * (rayOriginX - spherePosX)*rayDirX) + (2 * (rayOriginY - spherePosY)*rayDirY) + (2 * (rayOriginZ - spherePosZ)*rayDirZ);
		double c = pow(rayOriginX - spherePosX, 2) + pow(rayOriginY - spherePosY, 2) + pow(rayOriginZ - spherePosZ, 2) - (radius*radius);

		double discriminant = b * b - 4 * c;

		if (discriminant > 0) {
			double root1 = ((-1 * b - sqrt(discriminant)) / 2) - 0.000001;
			
			if (root1 > 0) {
				return root1;
			}
			else {
				double root2 = ((sqrt(discriminant) - b) / 2) - 0.000001;
				return root2;
			}
		}
		else {
			return -1;
		}

	}

};

Sphere::Sphere() {
	pos = Vect(0, 0, 0);
	radius = 1;
	color = Color(0.5, 0.5, 0.5, 0);
}

Sphere::Sphere(Vect p, double r, Color c) {
	pos = p;
	radius = r;
	color = c;
}

#endif