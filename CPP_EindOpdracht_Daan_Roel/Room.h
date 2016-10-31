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
	int GetCombinedHitPoints();


	// functies voor het toevoegen van dingen
	void Draw();
	void AddToys();
	void AddEnemies();
	// void AddDoors(); 
private:
	list<Enemy> enemies;
	Player player;
	bool visited;
	//map<std::string, Room> doors;
	
	// dit is voor de edges
	int combinedHitPoints;

	// opties
};

