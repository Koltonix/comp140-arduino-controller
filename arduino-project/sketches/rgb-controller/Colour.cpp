//////////////////////////////////////////////////
// Christopher Robertson
// MIT License Copyright (c) 2020
// Google C++ Style Guide
//////////////////////////////////////////////////

#include "math.h"
#include "colour.h"
#include "hsv.h"

using namespace std;

//Default Constructor Initialiser
Colour::Colour() : r(0), g(0), b(0) {}

//Assigns the RGB colour parameters to the respective public variables
Colour::Colour(int r, int g, int b) : r(r), g(g), b(b)
{
	int rgb[] = { r, g, b };
	int rgb_length = sizeof(rgb) / sizeof(rgb[0]);

	//Iterates through rgb values and does a sanity check to ensure
	//that they are between 0-255
	for (int i = 0; i < rgb_length; i++)
	{
		if (rgb[i] > 255) rgb[i] = 255;
		else if (rgb[i] < 0) rgb[i] = 0;
	}

	this->r = rgb[0];
	this->g = rgb[1];
	this->b = rgb[2];
}

//Converts a the hue, saturation and value parameters to an RGB value 
//and returns a Colour class where it is stored
//Source #1: https://stackoverflow.com/questions/3018313/algorithm-to-convert-rgb-to-hsv-and-hsv-to-rgb-in-range-0-255-for-both
//Source #2: https://www.programmingalgorithms.com/algorithm/hsv-to-rgb/
Colour Colour::HSVToRGB(double h, double s, double v)
{
	int i;
	
	double p;
	double q;
	double t;
	double ff;

	Colour colour;

	if (s <= 0.0)
	{
		v *= 255;
		colour.r = int(v);
		colour.g = int(v);
		colour.b = int(v);
		return colour;
	}

	//Sanity check to ensure the hue is between 0 and 360
	if (h >= 360.0) h = 0.0;
	else h /= 60.0;

	i = trunc(h);
	ff = h - i;

	p = 255 * v * (1.0 - s);
	p = 255 * v * (1.0 - s);
	q = 255 * v * (1.0 - (s * ff));
	t = 255 * v * (1.0 - (s * 1.0 - ff));

	v *= 255;

	switch (i) 
	{
	case 0:
		colour.r = int(v);
		colour.g = int(t);
		colour.b = int(p);
		break;
	case 1:
		colour.r = int(q);
		colour.g = int(v);
		colour.b = int(p);
		break;
	case 2:
		colour.r = int(p);
		colour.g = int(v);
		colour.b = int(t);
		break;

	case 3:
		colour.r = int(p);
		colour.g = int(q);
		colour.b = int(v);
		break;
	case 4:
		colour.r = int(t);
		colour.g = int(p);
		colour.b = int(v);
		break;
	case 5:
	default:
		colour.r = int(v);
		colour.g = int(p);
		colour.b = int(q);
		break;
	}

	return colour;
}