#pragma once
#include <queue>
#include "colour.h"

using namespace std;

class Lane 
{
public:
	int lane_index;

	queue <Colour> colour_order;

	Colour selected_colour;
	Colour *available_colours;

	float interval_to_change_colour;

	Lane(int index);

	void AddNewColour(Colour colour);
	void RemoveNextColour();

	Colour GetColourAtIndex(int index);
	Colour GetColourAtAngle(float angle);

	float GetCurrentPercentage();
	void SetCurrentPercentage(float p);

private:
	float current_percentage;

	bool NextColourIsCurrent(Colour current_colour);
};
