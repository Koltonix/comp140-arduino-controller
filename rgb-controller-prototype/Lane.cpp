#include "Lane.h"
#include "Colour.h"
#include <iostream>;

using namespace std;

Lane::Lane(int laneIndex)
{
	this->laneIndex = laneIndex;
}

void Lane::AddNewColour(Colour colour)
{
	colourOrder.push_front(colour);
}

Colour Lane::GetColourAtIndex(int index) 
{
	//Requires fixing
	/*if (colourOrder.size() > index)
	{
		list<Colour>::iterator colourIterator = colourOrder.begin();
		advance(colourIterator, index);

		Colour colour = *colourIterator;
		cout << colour.r << " R Value \n";
		return *colourIterator;
	}*/

	return Colour(0, 0, 0);
}