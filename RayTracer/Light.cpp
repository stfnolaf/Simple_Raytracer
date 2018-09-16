#include "pch.h"
#include "Light.h"

Light::Light() {
	pos = Vect(0, 0, 0);
	color = Color(1, 1, 1, 0);
}

Light::Light(Vect p, Color c) {
	pos = p;
	color = c;
}

Vect Light::getLightPos() { return pos; }

Color Light::getLightColor() { return color; }