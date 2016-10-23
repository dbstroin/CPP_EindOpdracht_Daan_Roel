#pragma once
#include <iostream>
#include <list>
#include <map>
#include "Enemy.h"
#include "Room.h"
#include "Player.h"

class Room
{
public:
	Room();
	~Room();
	int GetCombinedHitPoints();
private:
	list<Enemy> enemies;
	Player player;
	map<std::string, Room> doors;
	
	// dit is voor de edges
	int combinedHitPoints;

	// opties
};

