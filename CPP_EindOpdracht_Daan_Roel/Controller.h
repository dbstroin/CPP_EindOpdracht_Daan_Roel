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
	int AskForHeight();
	int AskForWidth();
	int AskForFloors();
	Player* AskForPlayer();
	int getAnswer(int amountOfOptions);
};

