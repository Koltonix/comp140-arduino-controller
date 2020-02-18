#pragma once
#include "Colour.cpp";

Colour::Colour(int r, int g, int b) : r(r), g(g), b(b)
{
	if (r > 255) this->r = 255;
}