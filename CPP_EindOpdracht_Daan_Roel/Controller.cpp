#include "stdafx.h"
#include <iostream>
#include <string>
#include "Controller.h"
#include "Dungeon.h"
#include <sstream>

Controller::Controller()
{
}

Controller::~Controller()
{
}

void Controller::StartGame()
{
	int floors = AskForFloors();
	int height = AskForHeight();
	int width = AskForWidth();
	player = AskForPlayer();

	Dungeon dungeon(width, height, floors, player);

	while (!dungeon.finished) dungeon.play();

	delete player;
}

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
	cin.ignore();
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

Player* Controller::AskForPlayer() {
	Player* p = new Player();
	cout << "Would you like to load an existing character or create a new one?" << endl;
	cout << "0: Load character" << endl;
	cout << "1: New character" << endl;
	int answer = getAnswer(2);
	if (answer == 0) {
		std::string input = "";

		while (input == "") {
			cout << "Select a character (write the character's name):" << endl;
			cin >> input;
		}
		cin.ignore();
		p->loadPlayer(input);

		if (p->getDamage() > 0) {
			return p;
		}
		else {
			cout << "Character: " << input << " does not exist, creating new character..." << endl;
			p->newPlayer();
		}
	}
	else {
		p->newPlayer();
	}
	return p;
}
