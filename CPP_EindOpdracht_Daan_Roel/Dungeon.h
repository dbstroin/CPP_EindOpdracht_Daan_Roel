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
	void tryItems();
	void tryMove();
	void tryNextFloor();
	vector<Floor> floors;
	Player* player;
	bool finished;
private:
	int length;
	int width;
	int layers;
	int currFloor;
};

