#include "Colour.h"

class Led
{
public:
	Colour *colour;
	int display_position;

	Led(Colour *colour, int display_position);
};