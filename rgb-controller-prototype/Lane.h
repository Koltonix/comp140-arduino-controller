#pragma once
#include <queue>
#include "Colour.h"

using namespace std;

class Lane 
{
public:
	int laneIndex;

	queue <Colour> colourQueue = queue<Colour>();

	Colour currentColour;
	Colour* availableColours = { new Colour(255, 255, 255) };

	Lane(int index);
	void AddNewColour(Colour* colour);
};
