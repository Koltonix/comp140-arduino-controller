#include "Colour.h"

class Led
{
public:
	Colour *colour;
	int displayPosition;

	Led(Colour *colour, int displayPosition);
};