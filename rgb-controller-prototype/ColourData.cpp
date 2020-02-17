#include "ColourData.h";

using RGB::CustomData::Colour32;

ColourData::ColourData() 
{	
	Colour32 colour(0, 0, 0);
	this->colour = colour;

	displayPosition = 0;
};

ColourData::ColourData(Colour32 colour, int displayPosition)
{
	this->colour = colour;
	this->displayPosition = displayPosition;
}