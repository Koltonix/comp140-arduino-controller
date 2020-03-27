#include "math.h"
#include <ctime>

#include "lane.h"
#include "colour.h"

Lane::Lane(int laneIndex)
{
	this->lane_index = laneIndex;
	this->colour_order = queue<Colour>();

	this->selected_colour = Colour(0, 0, 0);

	this->interval_to_change_colour = 360 / available_colours.size() - 1;
}

void Lane::AddNewColour(Colour colour)
{
	colour_order.push(colour);
}

void Lane::RemoveNextColour()
{
	this->colour_order.pop();
	this->colour_order.push(GetRandomColourPreset());
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

Colour Lane::GetColourAtAngle(float angle)
{
	if (angle > 360 || angle < 0) return Colour(0, 0, 0);

	int roundedToInterval = (angle + interval_to_change_colour / 2);
	roundedToInterval -= roundedToInterval % int(round(interval_to_change_colour));
	int colourIndex = (round(roundedToInterval) / 360) * available_colours.size() - 1;
	
	return available_colours[colourIndex];
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

bool Lane::NextColourIsCurrent(Colour current_colour)
{
	Colour next_colour = colour_order.front();

	int next_colour_values[] = { next_colour.r, next_colour.g, next_colour.b };
	int current_colour_values[] = { current_colour.r, current_colour.g, current_colour.b };
	int rgb_length = sizeof(next_colour_values) / sizeof(next_colour_values[0]);

	for (int i = 0; i < rgb_length; i++)
	{
		if (next_colour_values[i] != current_colour_values[i]) return false;
	}

	return true;
}

Colour Lane::GetRandomColourPreset()
{	
	int available_colours_length = available_colours.size() - 1;

	srand(time(NULL));
	int random_value = rand() % available_colours_length;
	cout << random_value << " random value" << endl;

	return available_colours[random_value];
}	