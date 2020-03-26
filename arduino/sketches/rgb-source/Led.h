#pragma once

#ifndef Led_h
#define Led_h

#include "colour.h"

class Led
{
public:
	Colour *colour;
	int display_position;

	Led(Colour *colour, int display_position);
};

#endif