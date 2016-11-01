#pragma once
#include "Room.h"
#include "Enemy.h"
#include <vector>

using namespace std;

class Floor
{
public:
	Floor();
	Floor(int l, int w, int lev);
	void drawMap();
	~Floor();
private:
	vector <vector<Room>> rooms;
	vector<Enemy> possibleEnemies;
	int level;
	int width;
	int length;
	void createEdges();
	void createRooms();

	void CreatePossibleEnemies();
	// functie om een random dungeon te maken.
};

