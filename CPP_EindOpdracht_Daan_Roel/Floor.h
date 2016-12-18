#pragma once
#include "Room.h"
#include "Enemy.h"
#include <vector>
#include "Globalfunc.h"
#include "FileReader.h"
#include <string>
#include <fstream>

using namespace std;

class Floor
{
public:
	Floor();
	Floor(int l, int w, int lev, Player* p);
	void clear();
	void drawMap();
	void setRandomStairs(int startx, int starty);
	void setStairsToPrevFloor(int x, int y);
	vector<string> getDirectionOptions();
	Enemy* tryEncounterEnemy();
	Enemy* getBoss() { return boss; }
	void setBossLocation();
	void deleteEnemy(Enemy * enemy);
	void useTalisman();
	bool getIfOnPlayerOnStairs();
	void movePlayer(int direction, vector<string> options);
	vector <vector<Room*>> rooms;
	~Floor();
private:
	bool started;
	Player* player;
	vector<Enemy*> possibleEnemies;
	vector<Enemy*> bosses;
	Enemy* boss;
	int level;
	int width;
	int length;
	void createEdges();
	void createRooms();
	void setStairsToNextFloor(int playerx, int playery);
	void createPossibleEnemies();

	void depthFirstSearch(Room* startRoom);
	void depthFirstSearch(Room* vertex, vector<Room*> visited);
	int breadthFirstSearch(Room* startRoom);

	// functie om een random dungeon te maken.
};

