#include <iostream>
#include <string>
#include <conio.h>

#include "Colour.h"
#include "Led.h"
#include "Lane.h"

using namespace std;

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

	Colour firstColour = Colour(255, 255, 255);
	Colour secondColour = Colour(128, 128, 128);
	Colour thirdColour = Colour(255, 255, 255);

	/*lane.AddNewColour(firstColour);
	lane.AddNewColour(secondColour);
	lane.AddNewColour(thirdColour);*/

	cout << "Colours Added" << endl;

	cout << firstColour.r << " long" << endl;

	cout << "Didn't run of course";

	//Colour colour = *lane.GetColourAtIndex(0);

	//std::cout << colour.r << ", "<< colour.g << ", " << colour.b << endl;
}

void Update()
{
	GetInput();
	std::cout << currentInput << endl;
}

int main()
{
	isRunning = false;
	Start();

	while (isRunning)
	{
		Update();
		cout << "running";
	}

	return 0;
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



