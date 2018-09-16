#pragma once

#ifndef _SOURCE_H
#define _SOURCE_H

#include "Vect.h"
#include "Color.h"

class Source {

public:
	Source();
	
	virtual Vect getLightPos();

	virtual Color getLightColor();

};
#endif
