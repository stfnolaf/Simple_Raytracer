#pragma once

#ifndef _COLOR_H
#define _COLOR_H

#include "math.h"

class Color {

	double red, green, blue, special;

public:

	Color();

	Color(double, double, double, double);

	//method functions
	double getRed();
	double getGreen();
	double getBlue();
	double getSpecial();

	void setRed(double redVal);
	void setGreen(double greenVal);
	void setBlue(double blueVal);
	void setSpecial(double specialVal);

	double brightness();

	Color colorScalar(double scalar);

	Color colorAdd(Color color);

	Color colorMultiply(Color color);

	Color colorAverage(Color color);

	Color clip();

};
#endif