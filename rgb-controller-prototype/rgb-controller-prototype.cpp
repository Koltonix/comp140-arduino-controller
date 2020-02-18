#include <iostream>
#include <string>
#include "Colour.h"

int main()
{
	Colour colour = Colour(255, 255, 255);
	
	std::cout << colour.r << ", " << colour.g << ", " << colour.b;
}
