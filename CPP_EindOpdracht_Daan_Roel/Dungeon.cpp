#include "stdafx.h"
#include "Dungeon.h"
#include <list>
#include <iostream>

using namespace std;

Dungeon::Dungeon(int w, int l, int f)
{
	list<Floor> floors;
	width = w;
	length = l;
	layers = f;
	for (int level = 0; level < layers; level++) {
		floors.push_back(AddFloor(width, length, level));
	}
	int h = 3;
	// floors.empty();
}

Dungeon::Dungeon()
{
}

Dungeon::~Dungeon()
{
}

Floor Dungeon::AddFloor(int width, int height, int level)
{
	Floor floor(width, height, level);

	// vul elke floor met kamers. Vul elke kamer met zooi en enemies.

	return floor;
}
