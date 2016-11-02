#pragma once
#include "Room.h"
#include "Enemy.h"
#include <vector>

using namespace std;

class Floor
{
public:
	Floor();
	Floor(int l, int w, int lev, Player* p);
	void clear();
	void drawMap();
	void startFloor(int startx, int starty);
	vector<string> getDirectionOptions();
	bool getIfOnPlayerOnStairs();
	void movePlayer(int direction, vector<string> options);
	vector <vector<Room*>> rooms;
	vector<Enemy *> getPossibleEnemies();
	~Floor();
private:
	Player* player;
	vector<Enemy *> possibleEnemies;
	int level;
	int width;
	int length;
	void createEdges();
	void createRooms();
	void createStairs(int playerx, int playery);
	void createPossibleEnemies();
	void depthFirstSearch(Room* startRoom);
	void depthFirstSearch(Room* vertex, vector<Room*> visited);
	void breathFirstSearch(Room* startRoom);

	// functie om een random dungeon te maken.
};

