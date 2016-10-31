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

	// functies voor het toevoegen van dingen
	void AddToys();
	void AddEnemies(Enemy e);
	// void AddDoors(); 
	int iets;
private:
	list<Enemy> enemies;
	Player player;
	bool visited;
	//map<std::string, Room> doors;
	
	// dit is voor de edges
	int combinedHitPoints;

	// opties
};

