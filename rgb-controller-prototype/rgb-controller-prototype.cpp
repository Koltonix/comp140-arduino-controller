#include <iostream>
#include <string>
#include <conio.h>

#include "Colour.h"
#include "Led.h"
#include "Lane.h"

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
	//Lane lane = Lane(0);

	//for (int i = 1; i < 4; i++)
	//{
	//	Colour newColour = Colour(i, i, i);
	//	lane.AddNewColour(newColour);
	//}

	//std::cout << lane.colourOrder.size() << " long\n";
	//Colour colour = lane.GetColourAtIndex(0);

	Colour *colour = new Colour(0, 0, 0);
	std::cout << colour->r << colour->g << colour->b << "\n";
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



