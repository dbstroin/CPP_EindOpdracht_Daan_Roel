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
	void tryEncounterItem();
	void tryEncounterEnemy();
	void Fight(Enemy * enemy);
	void tryItems();
	bool tryMove();
	void tryNextFloor();
	void fillEncounterableItems();
	int getAnswer(int amountOfOptions);
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

