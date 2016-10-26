#include "stdafx.h"
#include "Dungeon.h"
#include <list>
#include <iostream>

using namespace std;

Dungeon::Dungeon(int width, int height, int layers)
{
floors: new list<Floor>;
width: width;
height: height;
layers: layers;
	for (int level = 1; level < layers; level++) {
		floors.push_back(AddFloor(width, height, level));
	}
}

Dungeon::~Dungeon()
{
}

Floor Dungeon::AddFloor(int width, int height, int level)
{
	return new Floor(width, height, level);
}
