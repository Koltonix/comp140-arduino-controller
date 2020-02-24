#include <queue>
#include <iostream>

#include "Lane.h"
#include "Colour.h"

using namespace std;

Lane::Lane(int laneIndex)
{
	this->laneIndex = laneIndex;
	this->colourOrder = queue<Colour>();

	this->currentColour = Colour(0, 0, 0);
	this->availableColours = new Colour[1]{ Colour(0, 0, 0) };
}

void Lane::AddNewColour(Colour colour)
{
	colourOrder.push(colour);
}

//Colour *Lane::GetColourAtIndex(int index) 
//{
//	queue<Colour> _colourOrder = colourOrder;
//
//	cout << _colourOrder.size() << ", " << index << endl;
//
//	if (_colourOrder.size() > index)
//	{
//		cout << "Loop Starting" << endl;
//		for (int i = 0; i < index; i++)
//		{
//			cout << i << endl;
//			if (i == index)
//			{
//				return &_colourOrder.front();
//			}
//
//			
//			_colourOrder.pop();
//		}
//	}
//	
//	return new Colour(128, 128, 128);
//}