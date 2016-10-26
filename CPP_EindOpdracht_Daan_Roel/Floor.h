#pragma once
#include "Room.h"

using namespace std;

class Floor
{
public:
	Floor(int width, int height, int level);
	~Floor();
private:
	Room *rooms;
	int level;
};

