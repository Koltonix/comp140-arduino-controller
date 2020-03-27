
#ifndef Lane_h
#define Lane_h

#include "QList.h"
#include "colour.h"

using namespace std;

class Lane 
{
public:
	int lane_index;

	QList<Colour> colour_order;

	Colour selected_colour;
	QList<Colour> available_colours;

	float interval_to_change_colour;
	float current_percentage;

	Lane(int index);

	void AddNewColour(Colour colour);
	void RemoveNextColour(int random_modifier);

	Colour GetColourAtIndex(int index);
	Colour GetColourAtAngle(float angle);

	float GetCurrentPercentage();
	void SetCurrentPercentage(float p);

	Colour GetRandomColourPreset(int random_modifier);
	bool NextColourIsCurrent(Colour current_colour);	
};

#endif