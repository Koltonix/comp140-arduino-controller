//////////////////////////////////////////////////
// Christopher Robertson
// MIT License Copyright (c) 2020
// Google C++ Style Guide
//////////////////////////////////////////////////

#include "hsv.h"

///Default Constructor Initialiser
HSV::HSV() : h(0), s(0), v(0) {}
//Assigns the parameters immediately to the public variables
//WARNING: This does not currently include a sanity check
HSV::HSV(double h, double s, double v) : h(h), s(s), v(v) {}

//Takes in the red, blue and green (RGB) and converts it into the HSV format
//A HSV class is then returned with the new data.
//Source: https://stackoverflow.com/questions/3018313/algorithm-to-convert-rgb-to-hsv-and-hsv-to-rgb-in-range-0-255-for-both	
HSV HSV::RGBToHSV(int r, int g, int b)
{
	HSV hsv = HSV();

	//Normalising the rgb values from 0-1
	double _r = (double)r / 255;
	double _g = (double)g / 255;
	double _b = (double)b / 255;

	double min = _r < _g ? _r : _g;
	min = min < _b ? min : _b;

	double max = _r > _g ? _r : _g;
	max = max > _b ? max : _b;

	double delta = max - min;
	hsv.v = max;

	//Edge case check
	if (delta < 0.00001)
	{
		hsv.s = 0;
		hsv.h = 0;
		return hsv;
	}

	if (max > 0.0) hsv.s = (delta / max);

	else
	{
		hsv.s = 0;
		hsv.h = 0;
		return hsv;
	}

	hsv.v = max;

	if (max > 0) hsv.s = delta / max;

	if (_r >= max) hsv.h = (_g - _b) / delta;
	else if (_g >= max) hsv.h = 2.0 + (_b - _r) / delta;
	else if (_b >= max) hsv.h = 4.0 + (_r - _g) / delta;

	hsv.h *= 60.0;
	if (hsv.h < 0) hsv.h += 360.0;

	return hsv;
}