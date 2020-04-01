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
int num_leds = 8;
int score = 0;

//Rotary Encoder
int red_encoder_one = A0;
int green_encoder_one = A1;
int blue_encoder_one = A2;

int red_encoder_two = A3;
int green_encoder_two = A4;
int blue_encoder_two = A5;

int rotary_b_one = 2;
int rotary_a_one = 3;
int encoder_button_one = 4;

int rotary_b_two = 8;
int rotary_a_two = 9;
int encoder_button_two = 10;

//Lane 1 LEDS
int led_pin_one = 7;
int led_pin_two = 12;

//Lane 1
Lane first_lane = Lane(0, rotary_a_one, rotary_b_one, encoder_button_one, red_encoder_one, green_encoder_one, blue_encoder_one, num_leds, led_pin_one);
Lane second_lane = Lane(1, rotary_a_two, rotary_b_two, encoder_button_two, red_encoder_two, green_encoder_two, blue_encoder_two, num_leds, led_pin_two);

void setup() 
{
  Serial.begin(115200);

  LaneSetup(first_lane);
  //LaneSetup(second_lane);

  RotaryEncoderSetup(first_lane);
  //RotaryEncoderSetup(second_lane);
}

void loop() 
{
  if (can_input)
  {
    Serial.println(first_lane.time_since_last - millis() * 0.001f);
    if ((millis() - first_lane.time_since_last) * 0.001f > first_lane.default_time) Serial.println("LOST");

    UpdateLEDS(first_lane);
    //UpdateLEDS(second_lane, second_pixels);
    
    UpdateRotaryLEDs(first_lane); 
    //UpdateRotaryLEDs(second_lane);

    first_lane.SetCurrentPercentage(first_lane.current_percentage + (first_lane.interval_to_change_colour * float(first_lane.encoder_value)));

    //if (second_lane.encoder_value > 0) second_lane.SetCurrentPercentage(second_lane.current_percentage + turn_multiplier);
    //if (second_lane.encoder_value < 0) second_lane.SetCurrentPercentage(second_lane.current_percentage - turn_multiplier);

    if (digitalRead(first_lane.button) > 0)
    {
      if (first_lane.NextColourIsCurrent(first_lane.selected_colour))
      {
        first_lane.time_since_last = millis();

        Serial.println("CORRECT");
        first_lane.RemoveNextColour(millis());
        score++;
      }

      else 
      {
        Serial.println("INCORRECT"); 
        score--;
        
        PlayLoseAnimation(first_lane);
        GameOver();
      }
    }

    Serial.println(first_lane.current_percentage);
    Serial.println();
    Serial.println(String(first_lane.selected_colour.r) + ", " + String(first_lane.selected_colour.g) + ", " + String(first_lane.selected_colour.b));
    first_lane.encoder_value = 0;
  }
}

void LaneSetup(Lane &lane)
{
  lane.pixels->begin();
  first_lane.time_since_last = 0.0f;

  for (int i = 0; i < initial_lane_size; i++)
  {
    lane.AddNewColour(lane.GetRandomColourPreset(millis()));
    //Delayed since time is the key randomiser
    delay(100);
  }
}

void RotaryEncoderSetup(Lane &lane)
{ 
  pinMode(lane.rotary_a, INPUT_PULLUP);
  pinMode(lane.rotary_b, INPUT_PULLUP);
  pinMode(lane.button, OUTPUT);

  pinMode(lane.red_encoder, OUTPUT);
  pinMode(lane.green_encoder, OUTPUT);
  pinMode(lane.blue_encoder, OUTPUT);

  attachInterrupt(0, OnEncoderRotate, CHANGE);
}

void OnEncoderRotate()
{
  GetEncoderDirection(first_lane);
}

void GetEncoderDirection(Lane &lane)
{
  if (digitalRead(lane.rotary_a) == digitalRead(lane.rotary_b)) lane.encoder_value++;
  else lane.encoder_value--;
  lane.encoder_value = constrain(lane.encoder_value, -1, 1);
}

void UpdateLEDS(Lane& lane)
{  
  Colour first = lane.GetColourAtIndex(0);
  Colour second = lane.GetColourAtIndex(1);
  Colour third = lane.GetColourAtIndex(2);

  for (int i = 1; i <= num_leds; i++)
  {
    if (i % 3 != 0 || i == 0) 
    {
      if (i > 0 && i < 3) lane.pixels->setPixelColor(i - 1, lane.pixels->Color(round(third.r * led_brightness), round(third.g * led_brightness), round(third.b * led_brightness)));
      else if (i > 3 && i < 6) lane.pixels->setPixelColor(i - 1, lane.pixels->Color(round(second.r * led_brightness), round(second.g * led_brightness), round(second.b * led_brightness)));
      else if (i > 6) lane.pixels->setPixelColor(i - 1, lane.pixels->Color(round(first.r * led_brightness), round(first.g * led_brightness), round(first.b * led_brightness)));
    }
  }

  lane.pixels->show();
  delay(500);
}

void UpdateRotaryLEDs(Lane &lane)
{
  double r = double(lane.selected_colour.r) / double(255);
  double g = double(lane.selected_colour.g) / double(255);
  double b = double(lane.selected_colour.b) / double(255);

  digitalWrite(lane.red_encoder, 1.0 - r);
  digitalWrite(lane.green_encoder, 1.0 - g);
  digitalWrite(lane.blue_encoder, 1.0 - b);
}

void PlayLoseAnimation(Lane &lane)
{
  can_input = false;

  for (int j = 0; j < 3; j++)
  {
    for (int i = 0; i < lane.led_amount; i++)
    {
      lane.pixels->setPixelColor(i, lane.pixels->Color(255 * led_brightness, 0, 0));
    }

    lane.pixels->show();
    delay(500);

    for (int i = 0; i < lane.led_amount; i++)
    {
      lane.pixels->setPixelColor(i, lane.pixels->Color(0, 0, 0));
    }

    lane.pixels->show();
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
