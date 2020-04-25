//////////////////////////////////////////////////
// Christopher Robertson
// MIT License Copyright (c) 2020
// Google C++ Style Guide
//////////////////////////////////////////////////

#ifndef Colour_h
#define Colour_h

//Stores the data of the RGB colour wheel
//Also converts HSV values to RGB values
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