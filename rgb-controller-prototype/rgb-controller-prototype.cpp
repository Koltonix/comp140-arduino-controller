#include <iostream>
#include <string>
#include <conio.h>
#include <windows.h>

#include "colour.h"
#include "led.h"
#include "lane.h"

using namespace std;

enum InputType
{
	NONE,
	LEFT,
	RIGHT,
	QUIT,
};

bool is_running;
InputType current_input;

Lane lane = Lane(0);
float input_mutliplier = 20;

void Start();
void Update();
void GetInput();

void Start()
{
	Colour colour = Colour();
	colour = colour.HSVToRGB(45.0, 1.0, 1.0);

	cout << colour.r << ", " << colour.g << ", " << colour.b << endl;

}

void Update()
{
	GetInput();

	if (current_input == 1) lane.SetCurrentPercentage(lane.GetCurrentPercentage() + input_mutliplier);
	else if (current_input == 2) lane.SetCurrentPercentage(lane.GetCurrentPercentage() - input_mutliplier);
	cout << lane.GetCurrentPercentage() << endl;
}

int main()
{
	is_running = false;
	Start();

	while (is_running)
	{
		Update();
	}

	return 0;
}

void GetInput()
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



