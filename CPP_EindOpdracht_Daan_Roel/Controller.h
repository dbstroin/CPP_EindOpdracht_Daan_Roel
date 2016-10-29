#pragma once
#include "Dungeon.h"

class Controller
{
public:
	Controller();
	~Controller();
	void StartGame();
	bool RunGame();
private:
	Dungeon dungeon;
	int AskForHeight();
	int AskForWidth();
	int AskForFloors();
};

