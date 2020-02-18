#include <iostream>
#include <string>
#include "Colour.h"

int main()
{
    std::cout << "Hello World!\n";
	Colour colour = Colour(300, 128, 255);
	
	std::cout << colour.r << ", " << colour.g << ", " << colour.b;
}
