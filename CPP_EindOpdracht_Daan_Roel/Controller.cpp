#include "stdafx.h"
#include <iostream>
#include <string>
#include "Controller.h"

Controller::Controller()
{
}

Controller::~Controller()
{
}

vector<vector<Room>> test;

void Controller::StartGame()
{
	
	test.reserve(2);
	for (int i = 0; i < 2; i++)
	{
		Room b = Room(i, i, "over");
		vector<Room> temp;
		temp.reserve(1);
		temp.push_back(b);
		test.push_back(temp);
	}
	test.reserve(2);

	test[0][0].south = &test[1][0];
	test[1][0].north = &test[0][0];


	int floors = AskForFloors();
	int height = AskForHeight();
	int width = AskForWidth();

	dungeon = Dungeon(width, height, floors);
}

void Controller::hi() {
	test[0][0].south->playerVisits();
	int i = 3;
}

bool Controller::runGame()
{
	dungeon.play();
	return true;
}

//	functies die om user input vragen voor de dungeon grootte

int Controller::AskForHeight()
{
	bool correct = false;
	int height = 0;
	while (!correct) {
		// cin.clear zorgt ervoor dat de gebruiker opnieuw iets kan invoeren. Ik geef hier nog geen foutmelding. Zonder .clear kan de gebruiker maar 1 keer iets invoeren.
		cin.clear();
		cout << "Select a dungeon height (2 - 20):" << endl;
		cin >> height;
		if (height >= 2 && height <= 20) {
			correct = true;
		}
	}
	return height;
}

int Controller::AskForWidth()
{
	bool correct = false;
	int width = 0;
	while (!correct) {
		cin.clear();
		cout << "Select a dungeon width (2 - 20):" << endl;
		cin >> width;
		if (width >= 2 && width <= 20) {
			correct = true;
		}
	}
	return width;
}

int Controller::AskForFloors()
{
	bool correct = false;
	int floors = 0;
	while (!correct) {
		cin.clear();
		cout << "Select the amount of floors (1 - 10):" << endl;
		cin >> floors;
		if (floors >= 1 && floors <= 10) {
			correct = true;
		}
	}
	return floors;
}
