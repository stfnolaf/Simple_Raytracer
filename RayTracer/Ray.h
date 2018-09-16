#pragma once

#ifndef _RAY_H
#define _RAY_H

#include "Vect.h"

class Ray {

	Vect origin, dir;

public:

	Ray();

	Ray(Vect, Vect);

	//method functions
	Vect getRayOrigin();
	Vect getRayDir();

};

#endif