#include <iostream>
#include <string>

#include "Colour.h"
#include "Led.h"

int main()
{
	Colour colour = Colour(255, 255, 255);
	Led led = Led(&colour, 1);

	std::cout << led.colour->r << ", " << led.colour->g << ", " << led.colour->b;
}
