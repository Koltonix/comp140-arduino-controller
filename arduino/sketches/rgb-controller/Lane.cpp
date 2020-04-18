//////////////////////////////////////////////////
// Christopher Robertson
// MIT License Copyright (c) 2020
// Google C++ Style Guide
//////////////////////////////////////////////////

#include "Arduino.h"
#include "Adafruit_NeoPixel.h"
#include "math.h"
#include "time.h"

#include "lane.h"
#include "colour.h"

//Default Constructor
Lane::Lane(){}

//Constructor for the Lane which takes in the Arduino
//hardware inputs for the rotary encoder and rgb LED strip
Lane::Lane(int lane_index, int rotary_a, int rotary_b, int button, int red, int green, int blue, int led_amount, int led_pin)
{
	this->lane_index = lane_index;
	this->encoder_value = 0;

	this->rotary_a = rotary_a;
	this->rotary_b = rotary_b;
	this->button = button;
	
	this->red_encoder = red;
	this->green_encoder = green;
	this->blue_encoder = blue;
	
	this->led_amount = led_amount;
	this->led_pin = led_pin;

	this->colour_order = QList<Colour>();

	//Assigning the colours available to the Lane to pick from
	this->available_colours = QList<Colour>();
	this->available_colours.push_back(Colour(255, 0, 0)); //Red
	this->available_colours.push_back(Colour(0, 255, 0)); //Green
	this->available_colours.push_back(Colour(0, 0, 255)); //Blue
	this->available_colours.push_back(Colour(255, 255, 0)); //Yellow
	this->available_colours.push_back(Colour(0, 255, 255)); //Cyan
	this->available_colours.push_back(Colour(255, 0, 255)); //Magenta

	//Calculating the value at which to cycle to the next colour
	interval_to_change_colour = 360 / available_colours.size();
	SetCurrentAngle(interval_to_change_colour);

	//LED strip library initialisation
	this->pixels = new Adafruit_NeoPixel(led_amount, led_pin, NEO_GRB + NEO_KHZ800);
}

//Adds a new colour to the queue of colours to select
void Lane::AddNewColour(Colour colour)
{
	colour_order.push_front(colour);
}

//Removes the latest colour in the colour queue
//Takes in a random modifier which acts as the random seed
//which usually tends to be time related
void Lane::RemoveNextColour(int random_modifier)
{
	this->colour_order.pop_front();
	this->colour_order.push_back(GetRandomColourPreset(random_modifier));
}

//Gets the colour at the specified index
//Returns a colour class
Colour Lane::GetColourAtIndex(int index) 
{
	return this->colour_order.get(index);
}

//Calculates the index closest to the provided angle
Colour Lane::GetColourAtAngle(float angle)
{
	//Sanity check to ensure it is an euler angle
	if (angle > 360 || angle < 0) return Colour(0, 0, 0);

	int colourIndex = round(angle / 360.0 * available_colours.size() - 1);
	return available_colours[colourIndex];
}

//Getter for the current angle
float Lane::GetCurrentAngle()
{
	return this->current_angle;
}

//Setter for the current percentage variable
//A parameter is used to represent the direction as -1 is backwards,
// 0 is neutral, and  1 is forward
//This then assigns the current colour based on the current angle
void Lane::SetCurrentAngle(float direction)
{
	current_angle += (direction * interval_to_change_colour);

	//Sanity check to ensure it is in range of an euler angle
	if (current_angle > 360) current_angle = interval_to_change_colour;
	else if (current_angle <= 0) current_angle = 360;

	//Sets the currently selected colour
	this->selected_colour = GetColourAtAngle(current_angle);
}

//Checks to see if the selected colour is the same as the next colour
//Returns true if they are the same
bool Lane::NextColourIsCurrent(Colour current_colour)
{
	Colour next_colour = colour_order.front();

	//Storing the rgb values in arrays to be checked in an iterative way
	int next_colour_values[] = { next_colour.r, next_colour.g, next_colour.b };
	int current_colour_values[] = { current_colour.r, current_colour.g, current_colour.b };
	int rgb_length = sizeof(next_colour_values) / sizeof(next_colour_values[0]);

	//Returns false if any of the values do not match their respective counterpart
	for (int i = 0; i < rgb_length; i++)
	{
		if (next_colour_values[i] != current_colour_values[i]) return false;
	}

	return true;
}

//Gets a random colour from the array of available colours
//Requires a seed to produce a random effect which is usually time
Colour Lane::GetRandomColourPreset(int random_modifier)
{	
	int available_colours_length = available_colours.size() - 1;

	srand(random_modifier);
	int random_value = rand() % available_colours_length;
	
	return available_colours[random_value];
}	