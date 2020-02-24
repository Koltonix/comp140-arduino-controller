#include <iostream>
#include "Colour.h"
#include "HSV.h"

Colour::Colour() : r(0), g(0), b(0) {}
Colour::Colour(int r, int g, int b) : r(r), g(g), b(b)
{
	int rgb[] = { r, g, b };
	int arraySize = sizeof(rgb);

	std::cout << arraySize << std::endl;

	//Change the array size to produce the correct length
	for (int i = 0; i < 3; i++)
	{
		if (rgb[i] > 255) rgb[i] = 255;
		else if (rgb[i] < 0) rgb[i] = 0;
	}

	this->r = rgb[0];
	this->g = rgb[1];
	this->b = rgb[2];
}