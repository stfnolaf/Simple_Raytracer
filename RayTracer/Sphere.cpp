#include "pch.h"
#include "Sphere.h"

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

Vect Sphere::getSpherePos() {
	return pos;
}

double Sphere::getSphereRadius() {
	return radius;
}

Color Sphere::getColor() {
	return color;
}

Vect Sphere::getNormalAt(Vect point) {
	// normal always points away from center
	Vect normalVector = point.add(pos.negative()).normalize();
	return normalVector;
}

double Sphere::findIntersection(Ray ray) {
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