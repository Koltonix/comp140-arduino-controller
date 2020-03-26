#pragma once

#ifndef Colour_h
#define Colour_h

class Colour
{
public:
	int r;
	int g;
	int b;

	Colour();
	Colour(int r, int g, int b);

	Colour HSVToRGB(double h, double s, double v);
};

#endif