#include "stdafx.h"
#include "Floor.h"

Floor::Floor()
{
}

Floor::Floor(int l, int w, int lev)
{
	length = l;
	width = w;
	level = lev;
	rooms.reserve(w);
	//Fill grid with rooms
	for (int wIndex = 0; wIndex < w; wIndex++)
	{
		vector<Room> temp;
		
		for (int lIndex = 0; lIndex < l; lIndex++) {
			temp.push_back(Room(wIndex, lIndex));
		}
		
		rooms.push_back(temp);
	}
	
	//Connect rooms on ALL sides
	for (int wIndex = 0; wIndex < w; wIndex++)
	{

		for (int lIndex = 0; lIndex < l; lIndex++) {
			//East
			if (wIndex + 1 < w) {
				rooms[wIndex][lIndex].east = &rooms[wIndex + 1][lIndex];
			}
			//West
			if (wIndex - 1 > -1) {
				rooms[wIndex][lIndex].west = &rooms[wIndex - 1][lIndex];
			}
			//North
			if (lIndex - 1 > -1) {
				rooms[wIndex][lIndex].north = &rooms[wIndex][lIndex - 1];
			}
			//South
			if (lIndex + 1 < l) {
				rooms[wIndex][lIndex].south = &rooms[wIndex][lIndex + 1];
			}
		}

	}
	
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
