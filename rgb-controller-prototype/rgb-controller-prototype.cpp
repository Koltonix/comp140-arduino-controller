#include <iostream>
#include <string>
#include <conio.h>

#include "Colour.h"
#include "Led.h"

enum InputType
{
	LEFT,
	RIGHT,
	QUIT,
	NONE
};

bool isRunning;
InputType currentInput;

void Start();
void Update();
void GetInput();


void Start()
{
	Colour colour = Colour(97, 220, 134);
	Led led = Led(&colour, 1);

	HSV hsv = HSV();
	hsv = hsv.RGBToHSV(colour.r, colour.g, colour.b);

	std::cout << hsv.h << ", " << hsv.s << ", " << hsv.v;
}

void Update()
{
	GetInput();
	std::cout << currentInput << "\n";
}

int main()
{
	isRunning = false;
	Start();

	while (isRunning)
	{
		Update();
	}
}

void GetInput()
{
	if (_kbhit())
	{
		switch (_getch())
		{
			case 'a':
				currentInput = InputType(LEFT);
				break;
			case 'd':
				currentInput = InputType(RIGHT);
				break;
			case 'x':
				currentInput = InputType(QUIT);
				isRunning = false;
				break;
			default:
				currentInput = InputType(NONE);
				break;
		}
	}
}



