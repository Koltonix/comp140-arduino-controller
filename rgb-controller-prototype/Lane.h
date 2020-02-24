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

	Lane(int index);
	void AddNewColour(Colour colour);
	Colour GetColourAtIndex(int index);
};
