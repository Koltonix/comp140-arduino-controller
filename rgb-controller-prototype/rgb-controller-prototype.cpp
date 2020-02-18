#include <iostream>
#include <string>
#include <conio.h>

#include "Colour.h"
#include "Led.h"

enum InputType
{
	LEFT,
	RIGHT,
	EXIT,
	NONE
};

bool isRunning;
InputType currentInput;

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
				currentInput = InputType(EXIT);
				isRunning = false;
				break;
			default:
				currentInput = InputType(NONE);
				break;
		}
	}
}

void Start()
{
	Colour colour = Colour(255, 255, 255);
	Led led = Led(&colour, 1);

	std::cout << led.colour->r << ", " << led.colour->g << ", " << led.colour->b;
}

void Update()
{
	GetInput();
	std::cout << currentInput << "\n";
}

int main()
{
	isRunning = true;
	Start();

	while (isRunning)
	{
		Update();
	}
}

