#include "Colour.h"
#include "Lane.h"
#include "HSV.h"
#include "Led.h"

Lane first_lane = Lane(0);

void setup() 
{
  Serial.begin(115200);
  LaneSetup();
}

void loop() 
{
  
}

void LaneSetup()
{
  for (int i = 0; i < 4; i++)
  {
    first_lane.AddNewColour(first_lane.GetRandomColourPreset(millis()));

    Serial.println(first_lane.GetColourAtIndex(i).r);
    Serial.println(first_lane.GetColourAtIndex(i).g);
    Serial.println(first_lane.GetColourAtIndex(i).b);

    delay(1000);
  }
  
 
}
