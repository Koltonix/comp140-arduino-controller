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
	this->available_colours = new Colour[8]
	{
		Colour(255, 0, 0),
		Colour(255, 192, 0),
		Colour(128, 255, 0),
		Colour(0, 255, 255),
		Colour(0, 64, 255),
		Colour(128, 0, 255),
		Colour(255, 0, 192),
		Colour(255, 255, 0)
	};
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

float Lane::GetCurrentPercentage()
{
	return this->current_percentage;
}

void Lane::SetCurrentPercentage(float p)
{
	current_percentage = p;
	if (current_percentage > 360) current_percentage = 0;
	else if (current_percentage < 0) current_percentage = 360;
}