#pragma once
#pragma once

#ifndef _CAMERA_H
#define _CAMERA_H

#include "Vect.h"

class Camera {

	Vect pos, dir, right, up;

public:

	Camera();

	Camera(Vect, Vect, Vect, Vect);

	//method functions
	Vect getCameraPos();
	Vect getCameraDir();
	Vect getCameraRight();
	Vect getCameraUp();

};
#endif