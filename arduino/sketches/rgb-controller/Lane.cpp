#include "math.h"
#include "time.h"

#include "lane.h"
#include "colour.h"

Lane::Lane(int laneIndex)
{
	this->lane_index = laneIndex;
	
	this->colour_order = QList<Colour>();
	this->available_colours = QList<Colour>();

	this->available_colours.push_back(Colour(255, 0, 0));
	this->available_colours.push_back(Colour(255, 192, 0));
	this->available_colours.push_back(Colour(128, 255, 0));
	this->available_colours.push_back(Colour(0, 255, 255));
	this->available_colours.push_back(Colour(0, 64, 255));
	this->available_colours.push_back(Colour(128, 0, 255));
	this->available_colours.push_back(Colour(255, 0, 192));
	this->available_colours.push_back(Colour(255, 255, 0));

	this->selected_colour = Colour(0, 0, 0);

	this->interval_to_change_colour = 360 / available_colours.size() - 1;
}

void Lane::AddNewColour(Colour colour)
{
	colour_order.push_front(colour);
}

void Lane::RemoveNextColour(int random_modifier)
{
	this->colour_order.pop_front();
	this->colour_order.push_front(GetRandomColourPreset(random_modifier));
}

Colour Lane::GetColourAtIndex(int index) 
{
	return this->colour_order.get(0);;
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
	if (current_percentage > 360) current_percentage = current_percentage - 360;
	else if (current_percentage < 0) current_percentage = 360 + current_percentage;

	this->selected_colour = GetColourAtAngle(current_percentage);
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

Colour Lane::GetRandomColourPreset(int random_modifier)
{	
	int available_colours_length = available_colours.size() - 1;

	srand(random_modifier);
	int random_value = rand() % available_colours_length;
	
	return available_colours[random_value];
}	