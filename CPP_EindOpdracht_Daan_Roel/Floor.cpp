#include "stdafx.h"
#include "Floor.h"

Floor::Floor()
{
}

Floor::Floor(int l, int w, int lev)
{
	level = lev;
	rooms.reserve(w);
	for (int wIndex = 0; wIndex < w; wIndex++)
	{
		vector<Room> temp;
		
		for (int lIndex = 0; lIndex < l; lIndex++) {
			temp.push_back(Room(wIndex, lIndex));
		}
		
		rooms.push_back(temp);
	}
	int a = 2;
	drawMap();
}

void Floor::drawMap()
{
	//for (int wIndex = 0; wIndex < rooms.size; wIndex++) {
	//	for (int lIndex = 0; lIndex < rooms[wIndex].size; lIndex++) {

	//	}
	//}
}

Floor::~Floor()
{
}
