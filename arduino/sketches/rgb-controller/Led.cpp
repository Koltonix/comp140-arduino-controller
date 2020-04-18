//////////////////////////////////////////////////
// Christopher Robertson
// MIT License Copyright (c) 2020
// Google C++ Style Guide
//////////////////////////////////////////////////

#include "led.h"

//Constructor that takes in a colour parameter and the 
//position of the LED on the physical LED strip
Led::Led(Colour *colour, int display_position)
{
	this->colour = colour;
	this->display_position = display_position;
}