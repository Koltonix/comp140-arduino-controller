#include <Adafruit_NeoPixel.h>

#include "math.h"
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

int num_leds = 8;
int led_pin = 7;
float led_brightness = 0.1f;
Adafruit_NeoPixel first_pixels = Adafruit_NeoPixel(num_leds, led_pin, NEO_GRB + NEO_KHZ800);

int score = 0;

void setup() 
{
  Serial.begin(115200);
  LaneSetup();

  first_pixels.begin();
}

void loop() 
{
  UpdateLEDS();

  input = Serial.read();
  if (input == positive_input) first_lane.SetCurrentPercentage(first_lane.current_percentage + turn_multiplier);
  if (input == negative_input) first_lane.SetCurrentPercentage(first_lane.current_percentage - turn_multiplier);

  if (input == submit_input)
  {
    if (first_lane.NextColourIsCurrent(first_lane.selected_colour))
    {
      Serial.println("CORRECT");
      first_lane.RemoveNextColour(millis());
      score++;
    }

    else 
    {
      Serial.println("INCORRECT"); 
      score--;
    }
  }

  //Serial.println(GetStringFromColour(first_lane.colour_order.front()));
  //Serial.println(GetStringFromColour(first_lane.selected_colour));
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

void UpdateLEDS()
{
  Colour& current_colour = first_lane.selected_colour;
  for (int i = 0; i < num_leds; i+=2)
  {
    first_pixels.setPixelColor(i, first_pixels.Color(round(current_colour.r * led_brightness), round(current_colour.g * led_brightness), round(current_colour.b * led_brightness)));
  }

  first_pixels.show();
  delay(500);
}

String GetStringFromColour(Colour colour)
{
  String current_colour = String(colour.r) + ", " + String(colour.g) + ", " + String(colour.b);
  return current_colour;
}
