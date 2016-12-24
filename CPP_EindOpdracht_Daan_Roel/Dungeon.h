#pragma once
#include <iostream>
#include <list>
#include "Floor.h"
#include "Room.h"
#include "Globalfunc.h"

using namespace std;

class Dungeon
{
public:
	Dungeon(int width, int length, int floors, Player* p);
	void spawnPlayer();
	void setAllStairs();
	Dungeon();
	~Dungeon();
	void play();
	void tryEncounterItem();
	void tryEncounterEnemy();
	bool Fight(Enemy * enemy);
	void tryItems();
	bool tryBasicActions();
	void tryPrevFloor();
	void tryNextFloor();
	void finishDungeon();
	void playerDied();
	void fillEncounterableItems();
	vector<Floor> floors;
	Player* player;
	bool finished;
private:
	vector<Item*> encounterableItems;
	int length;
	int width;
	int layers;
	int currFloor;
};

