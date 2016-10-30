#pragma once
#include <iostream>
#include <list>
#include "Floor.h"


using namespace std;

class Dungeon
{
public:
	Dungeon(int width, int length, int floors);
	Dungeon();
	~Dungeon();
	Floor AddFloor(int width, int length, int level);
private:
	int length;
	int width;
	int layers;
	list<Floor> floors;
};

