#pragma once
#include <queue>
#include <list>
#include "Colour.h"

using namespace std;

class Lane 
{
public:
	int laneIndex;

	list <Colour> colourOrder = list<Colour>();

	Colour currentColour;
	Colour* availableColours = { new Colour(255, 255, 255) };

	Lane(int index);
	void AddNewColour(Colour colour);
	Colour GetColourAtIndex(int index);
};
