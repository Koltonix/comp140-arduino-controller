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

bool is_running;
InputType current_input;

void Start();
void Update();
void GetInput();

void Start()
{
	Lane lane = Lane(0);

	for (int i = 0; i < 3; i++)
	{
		lane.colour_order.push(Colour(i, i, i));
	}

	cout << "Colours Added" << endl;

	cout << lane.colour_order.size() << " long" << endl;


	Colour colour = lane.GetColourAtIndex(0);

	cout << colour.r << ", "<< colour.g << ", " << colour.b << endl;
}

void Update()
{
	GetInput();
	std::cout << current_input << endl;
}

int main()
{
	is_running = false;
	Start();

	while (is_running)
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
				current_input = InputType(LEFT);
				break;
			case 'd':
				current_input = InputType(RIGHT);
				break;
			case 'x':
				current_input = InputType(QUIT);
				is_running = false;
				break;
			default:
				current_input = InputType(NONE);
				break;
		}
	}
}



