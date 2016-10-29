#pragma once
#include "Room.h"

using namespace std;

class Floor
{
public:
	Floor();
	Floor(int width, int length, int level);
	~Floor();
private:
	Room *rooms;
	int level;

	// functie om een random dungeon te maken.
};

