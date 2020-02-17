#include "ColourData.cpp"

class LED
{
public:
	ColourData& colour;
	int displayPosition;

	LED(ColourData& colour, int displayPosition);
};
