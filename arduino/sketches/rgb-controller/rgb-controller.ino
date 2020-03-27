#include "Colour.h"
#include "Lane.h"
#include "HSV.h"
#include "Led.h"

char input;
char positive_input = 'e';
char negative_input = 'q';

int initial_lane_size = 3;
Lane first_lane = Lane(0);
float first_rotary_encoder = 0.0f;
float turn_multiplier = 2.0f;


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
  Serial.println(first_lane.current_percentage);
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
