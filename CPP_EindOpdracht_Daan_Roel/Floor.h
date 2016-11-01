#pragma once
#include "Room.h"
#include <vector>

using namespace std;

class Floor
{
public:
	Floor();
	Floor(int l, int w, int lev);
	void drawMap();
	void startFloor(int startx, int starty);
	vector<string> getDirectionOptions();
	void movePlayer(int direction, vector<string> options);
	~Floor();
private:
	vector <vector<Room>> rooms;
	int level;
	int width;
	int length;
	int playerx;
	int playery;
	void createEdges();
	void createRooms();

	void createStairs(int playerx, int playery);

	// functie om een random dungeon te maken.
};

