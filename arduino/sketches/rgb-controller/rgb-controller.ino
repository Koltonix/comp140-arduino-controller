#include <Adafruit_NeoPixel.h>

#include "math.h"
#include "Colour.h"
#include "Lane.h"
#include "HSV.h"
#include "Led.h"

//Game Conditions
bool can_input = true;
int initial_lane_size = 3;
float led_brightness = 0.1f;
float first_rotary_encoder = 0.0f;
float turn_multiplier = 45.0f;
int num_leds = 8;
int score = 0;

//Rotary Encoder
#define red_encoder_one A0
#define green_encoder_one A1
#define blue_encoder_one A2

#define red_encoder_two A3
#define green_encoder_two A4
#define blue_encoder_two A5

#define rotary_b_one 2
#define rotary_a_one 3
#define encoder_button_one 4

#define rotary_b_two 8
#define rotary_a_two 9
#define encoder_button_two 10

int encoder_value_one = 0;
int encoder_value_two = 0;

//Lane 1
Lane first_lane = Lane(0);
Lane second_lane = Lane(1);

//Lane 1 LEDS
int led_pin_one = 7;
int led_pin_two = 12;

Adafruit_NeoPixel first_pixels = Adafruit_NeoPixel(num_leds, led_pin_one, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel second_pixels = Adafruit_NeoPixel(num_leds, led_pin_two, NEO_GRB + NEO_KHZ800);


void setup() 
{
  Serial.begin(115200);

  LaneSetup(first_lane);
  LaneSetup(second_lane);

  RotaryEncoderSetup();

  first_pixels.begin();
  second_pixels.begin();
}

void loop() 
{
  if (can_input)
  {
    UpdateLEDS(first_lane, first_pixels);
    UpdateLEDS(second_lane, second_pixels);
    UpdateRotaryLEDs(); 

    if (encoder_value_one > 0) first_lane.SetCurrentPercentage(first_lane.current_percentage + turn_multiplier);
    if (encoder_value_one < 0) first_lane.SetCurrentPercentage(first_lane.current_percentage - turn_multiplier);

    if (encoder_value_two > 0) second_lane.SetCurrentPercentage(second_lane.current_percentage + turn_multiplier);
    if (encoder_value_two < 0) second_lane.SetCurrentPercentage(second_lane.current_percentage - turn_multiplier);

    if (digitalRead(encoder_button_one) > 0)
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

    encoder_value_one = 0;
    encoder_value_two = 0;
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
  pinMode(rotary_a_one, INPUT_PULLUP);
  pinMode(rotary_b_one, INPUT_PULLUP);
  pinMode(encoder_button_one, OUTPUT);

  pinMode(rotary_a_two, INPUT_PULLUP);
  pinMode(rotary_b_two, INPUT_PULLUP);
  pinMode(encoder_button_two, OUTPUT);

  pinMode(red_encoder_one, OUTPUT);
  pinMode(green_encoder_one, OUTPUT);
  pinMode(blue_encoder_one, OUTPUT);

  pinMode(red_encoder_two, OUTPUT);
  pinMode(green_encoder_two, OUTPUT);
  pinMode(blue_encoder_two, OUTPUT);

  attachInterrupt(0, OnFirstEncoderRotate, CHANGE);
  attachInterrupt(0, OnSecondEncoderRotate, CHANGE);
}

void OnFirstEncoderRotate()
{
  if (digitalRead(rotary_a_one) == digitalRead(rotary_b_one)) encoder_value_one++;
  else encoder_value_one--;
  encoder_value_one = constrain(encoder_value_one, -1, 1);
}

void OnSecondEncoderRotate()
{
  if (digitalRead(rotary_a_two) == digitalRead(rotary_b_two)) encoder_value_two++;
  else encoder_value_two--;
  encoder_value_two = constrain(encoder_value_two, -1, 1);
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

  digitalWrite(red_encoder_one, 1.0 - r);
  digitalWrite(green_encoder_one, 1.0 - g);
  digitalWrite(blue_encoder_one, 1.0 - b);
}

void PlayLoseAnimation(Adafruit_NeoPixel& pixels)
{
  can_input = false;

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
  can_input = true;
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
