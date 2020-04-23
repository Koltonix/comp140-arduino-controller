//////////////////////////////////////////////////
// Christopher Robertson
// MIT License Copyright (c) 2020
// Google C++ Style Guide
//////////////////////////////////////////////////

#ifndef Led_h
#define Led_h

#include "colour.h"

//Stores the current colour and position displayed at
//Obsolete now due to the Adafruit Library
class Led
{
public:
	Colour *colour;
	int display_position;

	Led(Colour *colour, int display_position);
};

#endif