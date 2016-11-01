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
	Room(int x, int y);
	int _x;
	int _y;
	string type;
	int GetCombinedHitPoints();
	Room* north;
	Room* east;
	Room* west;
	Room* south;


	// functies voor het toevoegen van dingen
	void Draw();
	void AddToys();
	void AddEnemies(Enemy e);
	// void AddDoors(); 
private:
	list<Enemy> enemies;
	Player player;
	bool visited;
	
	// dit is voor de edges
	int combinedHitPoints;

	// opties
};

