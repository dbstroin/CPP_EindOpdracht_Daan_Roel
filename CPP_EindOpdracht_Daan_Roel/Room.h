#pragma once
#include <iostream>
#include <vector>
#include "Enemy.h"
#include "Room.h"
#include "Player.h"
#include <vector>
#include <string>
#include "Globalfunc.h"

class Room
{
public:
	Room();
	~Room();
	Room(int x, int y, string t);
	int _x;
	int _y;
	int GetCombinedHitPoints();

	// functies voor het toevoegen van dingen
	void Draw();
	void AddToys();
	void setType(string t);
	string getType();
	void playerVisits();
	void playerLeaves();
	void setEnemy(Enemy * e);
	Enemy * getEnemy();
	vector<string> getAvailableDirections();
	Room * getEast();
	void setEast(Room * r);
	Room * getNorth();
	void setNorth(Room * r);
	Room * getWest();
	void setWest(Room * r);
	Room * getSouth();
	void setSouth(Room * r);
	void setSearchVisited(bool i);
	bool getSearchVisited();
	bool getVisited() { return visited; }
	bool searchVisited;
	vector<Room*> getAdjacentRooms();
	string getBeschrijving() { return beschrijving; }
	void setRandomBeschrijving();
	// void AddDoors(); 
private:
	string type;
	string beschrijving;

	Enemy* enemy;
	Player player;
	bool visited;
	bool visiting;

	Room* north;
	Room* east;
	Room* west;
	Room* south;
	
	vector<Room*> adjacentRooms;

	int combinedHitPoints;


};

