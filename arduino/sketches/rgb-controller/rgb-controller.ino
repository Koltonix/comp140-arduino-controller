#include "Colour.h"
#include "Lane.h"
#include "HSV.h"
#include "Led.h"

char input;
char positive_input = 'e';
char negative_input = 'q';
char submit_input = 'w';

int initial_lane_size = 3;
Lane first_lane = Lane(0);
float first_rotary_encoder = 0.0f;
float turn_multiplier = 45.0f;


void setup() 
{
  Serial.begin(9600);
  LaneSetup();
}

void loop() 
{
  input = Serial.read();
  if (input == positive_input) first_lane.SetCurrentPercentage(first_lane.current_percentage + turn_multiplier);
  if (input == negative_input) first_lane.SetCurrentPercentage(first_lane.current_percentage - turn_multiplier);

  if (input == submit_input && first_lane.NextColourIsCurrent(first_lane.selected_colour)) Serial.println("CORRECT");

  Serial.println(GetStringFromColour(first_lane.colour_order.front()));
  Serial.println(GetStringFromColour(first_lane.selected_colour));
}

void LaneSetup()
{
  for (int i = 0; i < initial_lane_size; i++)
  {
    first_lane.AddNewColour(first_lane.GetRandomColourPreset(millis()));

    Serial.println(first_lane.GetColourAtIndex(i).r);
    Serial.println(first_lane.GetColourAtIndex(i).g);
    Serial.println(first_lane.GetColourAtIndex(i).b);

    //Delayed since time is the key randomiser
    delay(10);
  }
}

String GetStringFromColour(Colour colour)
{
  String current_colour = String(colour.r) + ", " + String(colour.g) + ", " + String(colour.b);
  return current_colour;
}
