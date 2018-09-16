#pragma once

#ifndef _LIGHT_h
#define _LIGHT_h

#include "Source.h"
#include "Vect.h"
#include "Color.h"

class Light : public Source {

	Vect pos;
	Color color;

public:

	Light();

	Light(Vect, Color);

	//method functions
	virtual Vect getLightPos() { return pos; }
	virtual Color getLightColor() { return color; }

};

Light::Light() {
	pos = Vect(0, 0, 0);
	color = Color(1, 1, 1, 0);
}

Light::Light(Vect p, Color c) {
	pos = p;
	color = c;
}

#endif