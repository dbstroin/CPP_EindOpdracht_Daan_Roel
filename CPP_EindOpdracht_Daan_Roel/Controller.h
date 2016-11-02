#pragma once
#include "Dungeon.h"
#include "Player.h"

class Controller
{
public:
	Controller();
	~Controller();
	void StartGame();
	Player* player;
private:
	Dungeon dungeon;
	int AskForHeight();
	int AskForWidth();
	int AskForFloors();
	Player* AskForPlayer();
};

