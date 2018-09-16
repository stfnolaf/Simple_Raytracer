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
	virtual Vect getLightPos();
	virtual Color getLightColor();

};
#endif