
#ifndef Lane_h
#define Lane_h

#include <ArduinoSTL.h>
// #include <queue>
// #include <vector>
#include "colour.h"

using namespace std;

class Lane 
{
public:
	int lane_index;

	queue <Colour> colour_order;

	Colour selected_colour;
	vector<Colour> available_colours
	{
		Colour(255, 0, 0),
		Colour(255, 192, 0),
		Colour(128, 255, 0),
		Colour(0, 255, 255),
		Colour(0, 64, 255),
		Colour(128, 0, 255),
		Colour(255, 0, 192),
		Colour(255, 255, 0)
	};

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