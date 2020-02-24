#include <queue>
#include <iostream>

#include "Lane.h"
#include "Colour.h"

using namespace std;

Lane::Lane(int laneIndex)
{
	this->laneIndex = laneIndex;
	this->colourOrder = queue<Colour>();

	this->currentColour = Colour(0, 0, 0);
	this->availableColours = new Colour[1]{ Colour(0, 0, 0) };
}

void Lane::AddNewColour(Colour colour)
{
	colourOrder.push(colour);
}

Colour Lane::GetColourAtIndex(int index) 
{
	queue<Colour> _colourOrder = colourOrder;

	if (_colourOrder.size() > index)
	{
		for (int i = 0; i < _colourOrder.size(); i++)
		{
			if (i == index)
			{
				return _colourOrder.front();
			}

			_colourOrder.pop();
		}
	}
	
	return Colour(255, 255, 255);
}