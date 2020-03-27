#ifndef HSV_h
#define HSV_h

#include "colour.h"

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