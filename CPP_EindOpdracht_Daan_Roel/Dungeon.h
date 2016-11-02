#pragma once
#include <iostream>
#include <list>
#include "Floor.h"
#include "Room.h"


using namespace std;

class Dungeon
{
public:
	Dungeon(int width, int length, int floors);
	void spawnPlayer();
	Dungeon();
	~Dungeon();
	void play();
	void tryMove();
	void tryNextFloor();
	void tryFightingEnemy();
	vector<Floor> floors;
	bool finished;
private:
	int length;
	int width;
	int layers;
	int currFloor;
};

