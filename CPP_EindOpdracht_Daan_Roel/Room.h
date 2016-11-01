#pragma once
#include <iostream>
#include <list>
#include <map>
#include "Enemy.h"
#include "Room.h"
#include "Player.h"
#include <vector>
#include <string>

class Room
{
public:
	Room();
	~Room();
	Room(int x, int y, string t);
	int _x;
	int _y;
	int GetCombinedHitPoints();
	Room* north;
	Room* east;
	Room* west;
	Room* south;

	// functies voor het toevoegen van dingen
	void Draw();
	void AddToys();
	void AddEnemies(Enemy e);
	void setType(string t);
	void playerVisits();
	void playerLeaves();
	vector<string> getAvailableDirections();
	// void AddDoors(); 
private:
	string type;
	list<Enemy> enemies;
	Player player;
	bool visited;
	bool visiting;
	
	// dit is voor de edges
	int combinedHitPoints;

	// opties
};

