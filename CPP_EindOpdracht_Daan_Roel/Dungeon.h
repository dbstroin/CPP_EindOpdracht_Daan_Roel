#pragma once
#include <iostream>
#include <list>
#include "Floor.h"
#include "Room.h"


using namespace std;

class Dungeon
{
public:
	Dungeon(int width, int length, int floors, Player* p);
	void spawnPlayer();
	Dungeon();
	~Dungeon();
	void play();
	void tryMove();
	void tryNextFloor();
	void tryFightingEnemy();
	vector<Floor> floors;
	Player* player;
	bool finished;
private:
	int length;
	int width;
	int layers;
	int currFloor;
};

