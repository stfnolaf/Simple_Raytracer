#include "pch.h"
#include "Source.h"

Source::Source() {}

Vect Source::getLightPos() { return Vect(0, 0, 0); }

Color Source::getLightColor() { return Color(1, 1, 1, 0); }