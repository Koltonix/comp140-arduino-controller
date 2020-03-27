#include <Adafruit_NeoPixel.h>

#include "math.h"
#include "Colour.h"
#include "Lane.h"
#include "HSV.h"
#include "Led.h"

//Game Conditions
bool canInput = true;

//Rotary Encoder
#define redRotaryEncoder A1
#define greenRotaryEncoder A2
#define blueRotaryEncoder A3

#define rotaryB 2
#define rotaryA 3
#define encoderButton 4
int encoderValue = 0;

//Keyboard Input
char input;
char positive_input = 'e';
char negative_input = 'q';
char submit_input = 'w';

//Lane 1
int initial_lane_size = 3;
Lane first_lane = Lane(0);
float first_rotary_encoder = 0.0f;
float turn_multiplier = 45.0f;

//Lane 1 LEDS
int num_leds = 8;
int led_pin = 7;
float led_brightness = 0.1f;
Adafruit_NeoPixel first_pixels = Adafruit_NeoPixel(num_leds, led_pin, NEO_GRB + NEO_KHZ800);

int score = 0;

void setup() 
{
  Serial.begin(115200);
  LaneSetup();
  RotaryEncoderSetup();

  first_pixels.begin();
}

void loop() 
{
  if (canInput)
  {
    UpdateLEDS();

    input = Serial.read();
    if (encoderValue > 0) first_lane.SetCurrentPercentage(first_lane.current_percentage + turn_multiplier);
    if (encoderValue < 0) first_lane.SetCurrentPercentage(first_lane.current_percentage - turn_multiplier);

    if (digitalRead(encoderButton) > 0)
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
        
        PlayLoseAnimation();
        GameOver();
      }
    }

    //Serial.println(encoderValue);
    encoderValue = 0;
    //int btn = ;
    //Serial.println(btn);
    //lastEncoderValue = encoderValue;
    Serial.println(first_lane.current_percentage);
  }
  
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

void RotaryEncoderSetup()
{ 
  pinMode(rotaryA, INPUT_PULLUP);
  pinMode(rotaryB, INPUT_PULLUP);
  pinMode(encoderButton, OUTPUT);

  attachInterrupt(0, OnEncoderRotate, CHANGE);
}

void OnEncoderRotate()
{
  if (digitalRead(rotaryA) == digitalRead(rotaryB)) encoderValue++;
  else encoderValue--;
  encoderValue = constrain(encoderValue, -1, 1);
}

void UpdateLEDS()
{
  Colour& current_colour = first_lane.selected_colour;
  Colour next_colour = first_lane.GetColourAtIndex(0);

  for (int i = 0; i < num_leds; i+=2)
  {
    if (i < 4) first_pixels.setPixelColor(i, first_pixels.Color(round(current_colour.r * led_brightness), round(current_colour.g * led_brightness), round(current_colour.b * led_brightness)));
    else first_pixels.setPixelColor(i, first_pixels.Color(round(next_colour.r * led_brightness), round(next_colour.g * led_brightness), round(next_colour.b * led_brightness)));
  }

  first_pixels.show();
  delay(500);
}

void PlayLoseAnimation()
{
  canInput = false;

  for (int j = 0; j < 3; j++)
  {
    for (int i = 0; i < num_leds; i+=2)
    {
      first_pixels.setPixelColor(i, first_pixels.Color(255 * led_brightness, 0, 0));
    }

    first_pixels.show();
    delay(500);

    for (int i = 0; i < num_leds; i+=2)
    {
      first_pixels.setPixelColor(i, first_pixels.Color(0, 0, 0));
    }

    first_pixels.show();
    delay(500);
  }

  setup();
  canInput = true;
  
}

void GameOver()
{
  score = 0;
  setup();
}

String GetStringFromColour(Colour colour)
{
  String current_colour = String(colour.r) + ", " + String(colour.g) + ", " + String(colour.b);
  return current_colour;
}
