#include "Led.h"
#pragma once

Led::Led(Colour *colour, int displayPosition)
{
	this->colour = colour;
	this->displayPosition = displayPosition;
}