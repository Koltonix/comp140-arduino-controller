#include "Lane.h"
#include "Colour.h"

Lane::Lane(int laneIndex)
{
	this->laneIndex = laneIndex;
}

void Lane::AddNewColour(Colour *colour)
{
	colourQueue.push(*colour);
}