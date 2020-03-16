#include <iostream>
#include "colour.h"
#include "hsv.h"

Colour::Colour() : r(0), g(0), b(0) {}
Colour::Colour(int r, int g, int b) : r(r), g(g), b(b)
{
	int rgb[] = { r, g, b };
	int rgb_length = sizeof(rgb) / sizeof(rgb[0]);

	for (int i = 0; i < rgb_length; i++)
	{
		if (rgb[i] > 255) rgb[i] = 255;
		else if (rgb[i] < 0) rgb[i] = 0;
	}

	this->r = rgb[0];
	this->g = rgb[1];
	this->b = rgb[2];
}

//Source: https://stackoverflow.com/questions/3018313/algorithm-to-convert-rgb-to-hsv-and-hsv-to-rgb-in-range-0-255-for-both
Colour Colour::HSVToRGB(double h, double s, double v)
{
	double _h;
	double _s;
	double _v;

	long i;

	double p;
	double q;
	double t;
	double ff;

	Colour colour;

	if (s <= 0.0)
	{
		colour.r = v;
		colour.g = v;
		colour.b = v;
		return colour;
	}

	_h = h;
	if (_h >= 360) _h = 0.0;
	_h /= 60.0;

	i = long(_h);
	ff = h - i;
	
	p = v * (1.0 - s);
	q = v * (1.0 - (s * ff));
	t = v * (1.0 - (s * 1.0 - ff));

	switch (i) 
	{
	case 0:
		colour.r = v;
		colour.g = t;
		colour.b = p;
		break;

	case 1:
		colour.r = q;
		colour.g = v;
		colour.b = p;
		break;

	case 2:
		colour.r = p;
		colour.g = v;
		colour.b = t;
		break;

	case 3:
		colour.r = p;
		colour.g = q;
		colour.b = v;
		break;

	case 4:
		colour.r = t;
		colour.g = p;
		colour.b = v;
		break;

	case 5:
	default:
		colour.r = v;
		colour.g = p;
		colour.b = q;
		break;
	}

	return colour;
}