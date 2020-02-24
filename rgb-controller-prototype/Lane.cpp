#include <queue>
#include <iostream>

#include "lane.h"
#include "colour.h"

using namespace std;

Lane::Lane(int laneIndex)
{
	this->lane_index = laneIndex;
	this->colour_order = queue<Colour>();

	this->selected_colour = Colour(0, 0, 0);
	this->available_colours = new Colour[1]{ Colour(0, 0, 0) };
}

void Lane::AddNewColour(Colour colour)
{
	colour_order.push(colour);
}

Colour Lane::GetColourAtIndex(int index) 
{
	queue<Colour> _colourOrder = colour_order;

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