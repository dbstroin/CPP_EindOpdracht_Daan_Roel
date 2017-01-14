#pragma once
#include "Room.h"
#include "Enemy.h"
#include <vector>
#include "Globalfunc.h"
#include "FileReader.h"
#include <string>
#include <fstream>
#include <queue>
#include <unordered_map>

using namespace std;

class Floor
{
public:
	Floor();
	Floor(int l, int w, int lev, Player* p);
	void clear();
	void drawMap();
	std::pair<int, int> setStairsToNextFloor(int playerx, int playery);
	void setStairsToPrevFloor(int x, int y);
	vector<string> getDirectionOptions();
	Enemy* tryEncounterEnemy();
	Enemy* getBoss() { return boss; }
	void setBossLocation();
	void deleteEnemy(Enemy * enemy);
	void useTalisman();
	void resetSearchVisitedRooms();
	void randomizeFloor();
	void connectRandomRoom(int x, int y);
	bool getIfOnPlayerOnStairs();
	void movePlayer(int direction, vector<string> options);
	vector <vector<Room*>> rooms;
	~Floor();
private:
	Player* player;
	vector<Enemy*> possibleEnemies;
	Enemy* boss;
	int level;
	int width;
	int length;
	void createRooms();

	void createPossibleEnemies();

	void depthFirstSearch(Room* startRoom);
	void depthFirstSearch(Room* vertex, vector<Room*> visited);
	int breadthFirstSearch(Room * startRoom, int currentDistance);

	// functie om een random dungeon te maken.
};

