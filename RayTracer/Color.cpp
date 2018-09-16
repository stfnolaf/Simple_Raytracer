#include "pch.h"
#include "Color.h"

Color::Color() {
	red = 0.5;
	green = 0.5;
	blue = 0.5;
}

Color::Color(double r, double g, double b, double s) {
	red = r;
	green = g;
	blue = b;
	special = s;
}

double Color::getRed() {
	return red;
}

double Color::getGreen() {
	return green;
}

double Color::getBlue() {
	return blue;
}

double Color::getSpecial() {
	return special;
}

void Color::setRed(double redVal) {
	red = redVal;
}

void Color::setGreen(double greenVal) {
	green = greenVal;
}

void Color::setBlue(double blueVal) {
	blue = blueVal;
}

void Color::setSpecial(double specialVal) {
	special = specialVal;
}

double Color::brightness() {
	return (red + green + blue) / 3;
}

Color Color::colorScalar(double scalar) {
	return Color(red*scalar, green*scalar, blue*scalar, special);
}

Color Color::colorAdd(Color color) {
	return Color(red + color.getRed(), green + color.getGreen(), blue + color.getBlue(), special);
}

Color Color::colorMultiply(Color color) {
	return Color(red * color.getRed(), green * color.getGreen(), blue * color.getBlue(), special);
}

Color Color::colorAverage(Color color) {
	return Color((red + color.getRed()) / 2, (green + color.getGreen()) / 2, (blue + color.getBlue()) / 2, special);
}

Color Color::clip() {
	double alllight = red + green + blue;
	double excesslight = alllight - 3;
	if (excesslight > 0) {
		red = red + excesslight * (red / alllight);
		green = green + excesslight * (green / alllight);
		blue = blue + excesslight * (blue / alllight);
	}
	if (red > 1) { red = 1; }
	if (green > 1) { green = 1; }
	if (blue > 1) { blue = 1; }
	if (red < 0) { red = 0; }
	if (green < 0) { green = 0; }
	if (blue < 0) { blue = 0; }

	return Color(red, green, blue, special);

}