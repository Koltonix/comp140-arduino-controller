#include <Adafruit_NeoPixel.h>

#include "math.h"
#include "Colour.h"
#include "Lane.h"
#include "HSV.h"
#include "Led.h"

//Game Conditions
bool canInput = true;

//Rotary Encoder
#define redRotaryEncoderOne A1
#define greenRotaryEncoderOne A2
#define blueRotaryEncoderOne A3

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
  LaneSetup(first_lane);
  RotaryEncoderSetup();

  first_pixels.begin();
}

void loop() 
{
  if (canInput)
  {
    UpdateLEDS(first_lane, first_pixels);
    UpdateRotaryLEDs(); 

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
        
        PlayLoseAnimation(first_pixels);
        GameOver();
      }
    }

    encoderValue = 0;
    Serial.println(first_lane.current_percentage);
  }
  
}

void LaneSetup(Lane& lane)
{
  for (int i = 0; i < initial_lane_size; i++)
  {
    lane.AddNewColour(first_lane.GetRandomColourPreset(millis()));
    //Delayed since time is the key randomiser
    delay(100);
  }
}

void RotaryEncoderSetup()
{ 
  pinMode(rotaryA, INPUT_PULLUP);
  pinMode(rotaryB, INPUT_PULLUP);
  pinMode(encoderButton, OUTPUT);

  pinMode(redRotaryEncoderOne, OUTPUT);
  pinMode(greenRotaryEncoderOne, OUTPUT);
  pinMode(blueRotaryEncoderOne, OUTPUT);

  attachInterrupt(0, OnEncoderRotate, CHANGE);
}

void OnEncoderRotate()
{
  if (digitalRead(rotaryA) == digitalRead(rotaryB)) encoderValue++;
  else encoderValue--;
  encoderValue = constrain(encoderValue, -1, 1);
}

void UpdateLEDS(Lane& lane, Adafruit_NeoPixel& pixels)
{  
  Colour first = lane.GetColourAtIndex(0);
  Colour second = lane.GetColourAtIndex(1);
  Colour third = lane.GetColourAtIndex(2);

  for (int i = 1; i <= num_leds; i++)
  {
    if (i % 3 != 0 || i == 0) 
    {
      if (i > 0 && i < 3) pixels.setPixelColor(i - 1, pixels.Color(round(third.r * led_brightness), round(third.g * led_brightness), round(third.b * led_brightness)));
      else if (i > 3 && i < 6) pixels.setPixelColor(i - 1, pixels.Color(round(second.r * led_brightness), round(second.g * led_brightness), round(second.b * led_brightness)));
      else if (i > 6) pixels.setPixelColor(i - 1, pixels.Color(round(first.r * led_brightness), round(first.g * led_brightness), round(first.b * led_brightness)));
    }
  }

  pixels.show();
  delay(500);
}

void UpdateRotaryLEDs()
{
  double r = double(first_lane.selected_colour.r) / double(255);
  double g = double(first_lane.selected_colour.g) / double(255);
  double b = double(first_lane.selected_colour.b) / double(255);

  digitalWrite(redRotaryEncoderOne, 1.0 - r);
  digitalWrite(greenRotaryEncoderOne, 1.0 - g);
  digitalWrite(blueRotaryEncoderOne, 1.0 - b);
}

void PlayLoseAnimation(Adafruit_NeoPixel& pixels)
{
  canInput = false;

  for (int j = 0; j < 3; j++)
  {
    for (int i = 0; i < num_leds; i++)
    {
      pixels.setPixelColor(i, pixels.Color(255 * led_brightness, 0, 0));
    }

    first_pixels.show();
    delay(500);

    for (int i = 0; i < num_leds; i++)
    {
      pixels.setPixelColor(i, pixels.Color(0, 0, 0));
    }

    pixels.show();
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
