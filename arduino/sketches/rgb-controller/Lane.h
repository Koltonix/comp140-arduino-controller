//////////////////////////////////////////////////
// Christopher Robertson
// MIT License Copyright (c) 2020
// Google C++ Style Guide
//////////////////////////////////////////////////

#ifndef Lane_h
#define Lane_h

#include "QList.h"
#include "colour.h"

using namespace std;

//State handler for the Arduino Lane
//Stores all of the data related to the physical lane
//on the arduino board
class Lane 
{
public:
	int lane_index;
	int encoder_value = 0;

	int rotary_a;
	int rotary_b;
	int button;

	int red_encoder;
	int green_encoder;
	int blue_encoder;

	int led_amount;
	int led_pin;

	Adafruit_NeoPixel *pixels;

	QList<Colour> colour_order;

	Colour selected_colour;
	QList<Colour> available_colours;

	float interval_to_change_colour;
	float current_angle = 0.0f;

	float time_since_last = 0.0f;
	float default_time = 5.0f;

	Lane(int laneIndex, int rotary_a, int rotary_b, int button, int red, int green, int blue, int led_amount, int led_pin);

	void AddNewColour(Colour colour);
	void RemoveNextColour(int random_modifier);

	Colour GetColourAtIndex(int index);
	Colour GetColourAtAngle(float angle);

	float GetCurrentAngle();
	void SetCurrentAngle(float p);

	Colour GetRandomColourPreset(int random_modifier);
	bool NextColourIsCurrent(Colour current_colour);	
};

#endif