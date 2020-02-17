#include "Colour.h";

class ColourData
{
public:
	Colour colour;
	int displayPosition;

	ColourData(Colour colour, int displayPosition);
};

ColourData::ColourData(Colour _colour, int _displayPosition)
{
	colour = _colour;
	displayPosition = _displayPosition;
}
