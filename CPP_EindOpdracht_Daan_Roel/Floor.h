#pragma once
#include "Room.h"
#include <vector>

using namespace std;

class Floor
{
public:
	Floor();
	Floor(int length, int width, int level);
	void drawMap();
	~Floor();
private:
	vector <vector<Room>> rooms;
	int level;

	// functie om een random dungeon te maken.
};

