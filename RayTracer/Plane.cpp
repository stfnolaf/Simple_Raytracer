#include "pch.h"
#include "Plane.h"

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

Vect Plane::getNormal() {
	return normal;
}

double Plane::getPlaneDist() {
	return dist;
}
Color Plane::getColor() {
	return color;
}

Vect Plane::getNormalAt(Vect point) {
	return normal;
}

double Plane::findIntersection(Ray ray) {
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