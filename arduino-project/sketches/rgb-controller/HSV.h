//////////////////////////////////////////////////
// Christopher Robertson
// MIT License Copyright (c) 2020
// Google C++ Style Guide
//////////////////////////////////////////////////

#ifndef HSV_h
#define HSV_h

#include "colour.h"

//Stores the data of the HSV colour wheel
//Converts RGB values to HSV
class HSV
{
public:
	double h;
	double s;
	double v;

	HSV();
	HSV(double h, double s, double v);
	HSV RGBToHSV(int r, int g, int b);
};

#endif