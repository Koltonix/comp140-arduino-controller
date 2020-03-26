//Source: https://www.youtube.com/watch?v=mliaJrkme2U
#include <Adafruit_NeoPixel.h>

int NUMLEDS = 8;
int LEDPIN = 7;

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMLEDS, LEDPIN, NEO_GRB + NEO_KHZ800);

int delayValue = 500;

void setup() 
{ 
  pixels.begin();
  Serial.begin(9600);
}

void loop() 
{
  for (int i = 0; i < NUMLEDS; i++)
  {
    if (i < 4)pixels.setPixelColor(i, pixels.Color(128, 0, 0)); 
    else pixels.setPixelColor(i, pixels.Color(0, 0, 128)); 
  }

  pixels.show();
  delay(delayValue);
}
