#include "Led.h"
#pragma once

Led::Led(Colour *colour, int display_position)
{
	this->colour = colour;
	this->display_position = display_position;
}