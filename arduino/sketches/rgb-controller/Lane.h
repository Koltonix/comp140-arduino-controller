
#ifndef Lane_h
#define Lane_h

#include "QList.h"
// #include <queue>
// #include <vector>
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
	void RemoveNextColour();

	Colour GetColourAtIndex(int index);
	Colour GetColourAtAngle(float angle);

	float GetCurrentPercentage();
	void SetCurrentPercentage(float p);

	Colour GetRandomColourPreset();
	bool NextColourIsCurrent(Colour current_colour);	
	
private:
	
};

#endif