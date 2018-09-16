#pragma once

#ifndef _COLOR_H
#define _COLOR_H

#include "math.h"

class Color {

	float red, green, blue, special;

public:

	Color();

	Color(float, float, float, float);

	//method functions
	float getColorRed() { return red; }
	float getColorGreen() { return green; }
	float getColorBlue() { return blue; }
	float getColorSpecial() { return special; }

	void setColorRed(float redVal) { red = redVal; };
	void setColorGreen(float greenVal) { green = greenVal; };
	void setColorBlue(float blueVal) { blue = blueVal; };
	void setColorSpecial(float specialVal) { special = specialVal; };

	float brightness() {
		return (red + green + blue) / 3;
	}

	Color colorScalar(float scalar) {
		return Color(red*scalar, green*scalar, blue*scalar, special);
	}

	Color colorAdd(Color color) {
		return Color(red + color.getColorRed(), green + color.getColorGreen(), blue + color.getColorBlue(), special);
	}

	Color colorMultiply(Color color) {
		return Color(red * color.getColorRed(), green * color.getColorGreen(), blue * color.getColorBlue(), special);
	}

	Color colorAverage(Color color) {
		return Color((red + color.getColorRed()) / 2, (green + color.getColorGreen()) / 2, (blue + color.getColorBlue()) / 2, special);
	}

	Color clip() {
		double alllight = red + green + blue;
		double excesslight = alllight - 3.0f;
		if (excesslight > 0.0f) {
			red = red + excesslight * (red / alllight);
			green = green + excesslight * (green / alllight);
			blue = blue + excesslight * (blue / alllight);
		}
		if (red > 1.0f) { red = 1.0f; }
		if (green > 1.0f) { green = 1.0f; }
		if (blue > 1.0f) { blue = 1.0f; }
		if (red < 0.0f) { red = 0.0f; }
		if (green < 0.0f) { green = 0.0f; }
		if (blue < 0.0f) { blue = 0.0f; }

		return Color(red, green, blue, special);

	}

};

Color::Color() {
	red = 0.5f;
	green = 0.5f;
	blue = 0.5f;
}

Color::Color(float r, float g, float b, float s) {
	red = r;
	green = g;
	blue = b;
	special = s;
}

#endif