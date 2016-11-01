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
	~Floor();
private:
	vector <vector<Room>> rooms;
	int level;
	int width;
	int length;

	// functie om een random dungeon te maken.
};

