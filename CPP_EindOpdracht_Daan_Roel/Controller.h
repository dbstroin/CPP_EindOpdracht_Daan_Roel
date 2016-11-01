#pragma once
#include "Dungeon.h"

class Controller
{
public:
	Controller();
	~Controller();
	void StartGame();
	void hi();
	bool runGame();
private:
	Dungeon dungeon;
	int AskForHeight();
	int AskForWidth();
	int AskForFloors();
};

