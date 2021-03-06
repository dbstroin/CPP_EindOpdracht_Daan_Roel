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
	enum direction { EAST, NORTH, SOUTH, WEST };
	void clear();
	void drawMap();
	void drawMapHitpoints();
	std::pair<int, int> setStairsToNextFloor(int playerx, int playery);
	void setStairsToPrevFloor(int x, int y);
	vector<string> getDirectionOptions();
	Enemy* tryEncounterEnemy();
	Enemy * getEnemy(int x, int y);
	void deleteEnemy(Enemy * enemy, int x, int y);
	Enemy getBoss() { return boss; }
	void setBossLocation();
	void useTalisman();
	void useCompass();
	void useGrenade();
	void primsAlgorithm(Room * startRoom);
	void primsAlgorithm(Room * startRoom, direction d);
	void removeTooManyCollapsedRooms();
	void resetSearchVisitedRooms();
	void randomizeFloor();
	void addTauntEnemy(int xPos, int yPos);
	void setEdgeCosts();
	void connectRandomRoom(int x, int y);
	bool getIfOnPlayerOnStairs();
	void movePlayer(int direction, vector<string> options);
	vector <vector<Room*>> rooms;
	bool grenadeUsed = false;
	~Floor();
	
private:
	Player* player;
	vector<Enemy*> possibleEnemies;
	Enemy boss;
	int level;
	int width;
	int length;
	void createRooms();
	void setEnemyLocations();
	void createPossibleEnemies();
	void depthFirstSearch(Room* startRoom);
	void depthFirstSearch(Room* vertex, vector<Room*> visited);
	int breadthFirstSearch(Room * startRoom, int currentDistance);
	std::vector<std::string> dijkstraSearch(Room* startRoom);

	// functie om een random dungeon te maken.
};

