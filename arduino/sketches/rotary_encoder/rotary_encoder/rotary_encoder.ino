#include <PinChangeInt.h>

// LilyPad MP3 pin defines. Not all of these are used in this
// sketch; the unused pins are commented out:

#define ROT_LEDG A1     // green LED
#define ROT_B A3        // rotary B
#define ROT_A 3          // rotary A
#define ROT_SW 4         // rotary puhbutton
#define ROT_LEDB 5       // blue LED
#define ROT_LEDR 10      // red LED

// RGB LED colors (for common anode LED, 0 is on, 1 is off)
#define OFF B111
#define RED B110
#define GREEN B101
#define YELLOW B100
#define BLUE B011
#define PURPLE B010
#define CYAN B001
#define WHITE B000

// Global variables that can be changed in interrupt routines
volatile int rotary_counter = 0; // current "position" of rotary encoder (increments CW)
volatile boolean rotary_change = false; // will turn true if rotary_counter has changed
volatile boolean button_pressed = false; // will turn true if the button has been pushed
volatile boolean button_released = false; // will turn true if the button has been released (sets button_downtime)
volatile unsigned long button_downtime = 0L; // ms the button was pushed before release

// "Static" variables are initalized once the first time
// that loop runs, but they keep their values through
// successive loops.

static unsigned char x = 0; //LED color
static boolean button_down = false;
static unsigned long int button_down_start, button_down_time;

void setup()
{
  // Set up all the I/O pins. Unused pins are commented out.
  pinMode(ROT_B, INPUT);
  digitalWrite(ROT_B, HIGH); // turn on weak pullup
  pinMode(ROT_A, INPUT);
  digitalWrite(ROT_A, HIGH); // turn on weak pullup
  pinMode(ROT_SW, INPUT);
  // The rotary switch is common anode with external pulldown, do not turn on pullup
  pinMode(ROT_LEDB, OUTPUT);
  pinMode(ROT_LEDG, OUTPUT);
  pinMode(ROT_LEDR, OUTPUT);

  setLED(WHITE);

  Serial.begin(9600); // Use serial for debugging
  Serial.println("Begin RGB Rotary Encoder Testing");

  // We use the standard external interrupt pin for the rotary,
  // but we'll use the pin change interrupt library for the button.

  attachInterrupt(1, rotaryIRQ, CHANGE);
}

void rotaryIRQ()
{
  // Process input from the rotary encoder.
  // The rotary "position" is held in rotary_counter, increasing for CW rotation (changes by one per detent).
  // If the position changes, rotary_change will be set true. (You may manually set this to false after handling the change).

  // This function will automatically run when rotary encoder input A transitions in either direction (low to high or high to low)
  // By saving the state of the A and B pins through two interrupts, we'll determine the direction of rotation
  // int rotary_counter will be updated with the new value, and boolean rotary_change will be true if there was a value change
  // Based on concepts from Oleg at circuits@home (http://www.circuitsathome.com/mcu/rotary-encoder-interrupt-service-routine-for-avr-micros)
  // Unlike Oleg's original code, this code uses only one interrupt and has only two transition states;
  // it has less resolution but needs only one interrupt, is very smooth, and handles switchbounce well.

  static unsigned char rotary_state = 0; // current and previous encoder states

  rotary_state <<= 2;  // remember previous state
  rotary_state |= (digitalRead(ROT_A) | (digitalRead(ROT_B) << 1));  // mask in current state
  rotary_state &= 0x0F; // zero upper nybble

  //Serial.println(rotary_state,HEX);

  if (rotary_state == 0x09) // from 10 to 01, increment counter. Also try 0x06 if unreliable
  {
    rotary_counter++;
    rotary_change = true;
  }
  else if (rotary_state == 0x03) // from 00 to 11, decrement counter. Also try 0x0C if unreliable
  {
    rotary_counter--;
    rotary_change = true;
  }
}


void loop()
{
  // The rotary IRQ sets the flag rotary_counter to true
  // if the knob position has changed. We can use this flag
  // to do something in the main loop() each time there's
  // a change. We'll clear this flag when we're done, so
  // that we'll only do this if() once for each change.

  if (rotary_change)
  {
    Serial.print("rotary: ");
    Serial.println(rotary_counter, DEC);
    rotary_change = false; // Clear flag

    //blink for visual feedback
    setLED(OFF);
    delay(10); //try not to make this too long, otherwise the Arduino will miss ticks
    setLED(x);
  }

  // The button IRQ also sets flags to true, one for
  // button_pressed, one for button_released. Like the rotary
  // flag, we'll clear these when we're done handling them.

  Serial.println(digitalRead(4));
  if (button_pressed)
  {
    Serial.println("button press");
    button_pressed = false; // Clear flag
    button_down = true;
  }
}


void setLED(unsigned char color)
// Set RGB LED to one of eight colors (see #defines above)
{
  digitalWrite(ROT_LEDR, color & B001);
  digitalWrite(ROT_LEDG, color & B010);
  digitalWrite(ROT_LEDB, color & B100);
}
