//////////////////////////////////////////////////
// Christopher Robertson
// MIT License Copyright (c) 2020
// Google C++ Style Guide
//
// Handles the input from the Arduino Input
// Handles the output to external softwares like Unit
// Handes the state of the overall game on all lanes
//////////////////////////////////////////////////

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

//Rotary Encoder Ports
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

//Lane LED Ports
int led_pin_one = 7;
int led_pin_two = 12;

//Lane References
Lane first_lane = Lane(0, rotary_a_one, rotary_b_one, encoder_button_one, red_encoder_one, green_encoder_one, blue_encoder_one, num_leds, led_pin_one);
Lane second_lane = Lane(1, rotary_a_two, rotary_b_two, encoder_button_two, red_encoder_two, green_encoder_two, blue_encoder_two, num_leds, led_pin_two);

Lane lanes[] = {first_lane, second_lane};

//External Input
String incomingString;

void setup() 
{
  Serial.begin(115200);

  LaneSetup(first_lane);
  LaneSetup(second_lane);

  RotaryEncoderSetup(first_lane);
  RotaryEncoderSetup(second_lane);
  
  attachInterrupt(digitalPinToInterrupt(first_lane.rotary_a), OnFirstEncoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(second_lane.rotary_a), OnSecondEncoder, CHANGE);
}



void loop() 
{
  SendByteInput();

  if (can_input)
  {
    //Serial.println(first_lane.time_since_last - millis() * 0.001f);
    //if ((millis() - first_lane.time_since_last) * 0.001f > first_lane.default_time) Serial.println("LOST");

    UpdateLane(first_lane);
    //UpdateLane(second_lane);
  }
}

//Sends a string of data depending on the provided string provided in the console
//For example: encoderValue0 would return the encoder value of lane 0
void SendByteInput()
{
  if (Serial.available() > 0)
  {
    incomingString = Serial.readString();

    //Has to be done due to VSCode Arduino Extension and 
    //how it enters the string as the last two are always blank
    incomingString.remove(incomingString.length() - 1);
    incomingString.remove(incomingString.length() - 1);

    int laneIndex = incomingString[incomingString.length() - 1] - 48;
    if (laneIndex > (sizeof(lanes) / sizeof(lanes[0])) - 1) return;
    Lane* lane = &lanes[laneIndex];

    //Removing the unique lane identifier number
    incomingString.remove(incomingString.length() - 1);
    Serial.println(incomingString);
    if (incomingString == "encoderValue")
    {
      Serial.println(lane->current_angle);
      Serial.println(lanes[laneIndex].current_angle);
      Serial.println(first_lane.current_angle);
      //Serial.write(lane.current_percentage);
    }
  }
}


//Updates for the Lane using a lane reference to modify and read
void UpdateLane(Lane &lane)
{
    UpdateLEDS(lane);
    UpdateRotaryLEDs(lane); 

    first_lane.SetCurrentAngle(lane.encoder_value);

    //If the rotary encoder button has bee pressed
    if (digitalRead(first_lane.button) > 0)
    {
      //Successful push
      if (lane.NextColourIsCurrent(lane.selected_colour))
      {
        lane.time_since_last = millis();

        Serial.println("CORRECT");
        lane.RemoveNextColour(millis());
        score++;
      }

      //Failed push
      else 
      {
        Serial.println("INCORRECT"); 
        score--;
        
        PlayLoseAnimation(lane);
        GameOver();
      }
    }

    //Serial.println(String(lane.lane_index) + ": " + String(first_lane.current_percentage));
    //Serial.println(String(first_lane.selected_colour.r) + ", " + String(first_lane.selected_colour.g) + ", " + String(first_lane.selected_colour.b));
    lane.encoder_value = 0;
}

//Initial Setup of a lane using a lane reference
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

//Initial Setup of the Arduino Ports for the rotary encoder and
//the LED strip using a lane class to read from
void RotaryEncoderSetup(Lane &lane)
{ 
  pinMode(lane.rotary_a, INPUT_PULLUP);
  pinMode(lane.rotary_b, INPUT_PULLUP);
  pinMode(lane.button, OUTPUT);

  pinMode(lane.red_encoder, OUTPUT);
  pinMode(lane.green_encoder, OUTPUT);
  pinMode(lane.blue_encoder, OUTPUT);
}


//Separate function is required to attach to the interrupt in the setup
//Calls the function to change the direction using a lane reference
void OnFirstEncoder()
{
  GetEncoderDirection(first_lane);
}

//Separate function is required to attach to the interrupt in the setup
//Calls the function to change the direction using a lane reference
void OnSecondEncoder()
{
  GetEncoderDirection(second_lane);
}

//Changes the encoder value of the rotary encoder using
//the direction change
//Uses a lane reference to read and write to
void GetEncoderDirection(Lane &lane)
{
  if (digitalRead(lane.rotary_a) == digitalRead(lane.rotary_b)) lane.encoder_value++;
  else lane.encoder_value--;

  lane.encoder_value = constrain(lane.encoder_value, -1, 1);
}

//Updating the physical LEDs 
//Uses a lane reference to get the colours and then
//sets the LED colours using it's Adafruit_NeoPixel class
void UpdateLEDS(Lane& lane)
{  
  Colour first = lane.GetColourAtIndex(0);
  Colour second = lane.GetColourAtIndex(1);
  Colour third = lane.GetColourAtIndex(2);

  for (int i = 1; i <= num_leds; i++)
  {
    //Only LEDs that are not multiples of 3
    //The reason for this is the physical design of the 
    //controller and how it has been built by
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

//Updates the rotary encoder RGB light 
//Uses a Lane reference to read the selected colour from
void UpdateRotaryLEDs(Lane &lane)
{
  double r = double(lane.selected_colour.r) / double(255);
  double g = double(lane.selected_colour.g) / double(255);
  double b = double(lane.selected_colour.b) / double(255);

  digitalWrite(lane.red_encoder, 1.0 - r);
  digitalWrite(lane.green_encoder, 1.0 - g);
  digitalWrite(lane.blue_encoder, 1.0 - b);
}

//Plays a short lose animation on the Lane LEDs provided
void PlayLoseAnimation(Lane &lane)
{
  can_input = false;

  //Blinking Three Times
  for (int j = 0; j < 3; j++)
  {
    //Red Blink
    for (int i = 0; i < lane.led_amount; i++)
    {
      lane.pixels->setPixelColor(i, lane.pixels->Color(255 * led_brightness, 0, 0));
    }

    lane.pixels->show();
    delay(500);

    //No Light
    for (int i = 0; i < lane.led_amount; i++)
    {
      lane.pixels->setPixelColor(i, lane.pixels->Color(0, 0, 0));
    }

    lane.pixels->show();
    delay(500);
  }

  //Restarting the Game
  GameOver();
  can_input = true;
}

//Resets the Game Values
void GameOver()
{
  score = 0;
  setup();
}

//Returns a String based on the colour class provided
String GetStringFromColour(Colour colour)
{
  String current_colour = String(colour.r) + ", " + String(colour.g) + ", " + String(colour.b);
  return current_colour;
}
