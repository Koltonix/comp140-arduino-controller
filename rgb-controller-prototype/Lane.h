#pragma once
#include <queue>
#include "Colour.h"

using namespace std;

class Lane 
{
public:
	int laneIndex;

	queue <Colour> colourOrder;

	Colour currentColour;
	Colour *availableColours;

	Lane(int index);
	void AddNewColour(Colour colour);
	Colour *GetColourAtIndex(int index);
};
