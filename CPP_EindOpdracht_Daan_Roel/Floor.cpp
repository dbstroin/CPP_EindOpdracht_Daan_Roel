#include "stdafx.h"
#include "Floor.h"

Floor::Floor()
{
}

void Floor::drawMap()
{
	for (int lIndex = 0; lIndex < length; lIndex++) {
		for (int wIndex = 0; wIndex < width; wIndex++) {
			if (rooms[wIndex][lIndex].north != nullptr) {			
				cout << "| ";
			}
		}

		cout << endl;

		for (int wIndex = 0; wIndex < width; wIndex++) {
			rooms[wIndex][lIndex].Draw();
			if (rooms[wIndex][lIndex].east != nullptr) {
				cout << "-";
			}
		}
		cout << endl;
	}

}

Floor::Floor(int l, int w, int lev)
{
	length = l;
	width = w;
	level = lev;

	createRooms();
	createEdges();

}



Floor::~Floor()
{
}

void Floor::createEdges()
{
	//Connect rooms on ALL sides
	for (int wIndex = 0; wIndex < width; wIndex++)
	{
		for (int lIndex = 0; lIndex < length; lIndex++) {
			//East
			if (wIndex + 1 < width) {
				rooms[wIndex][lIndex].east = new Room();
				(*rooms[wIndex][lIndex].east) = rooms[wIndex + 1][lIndex];
			}
			else {
				rooms[wIndex][lIndex].east = nullptr;
			}
			//West
			if (wIndex - 1 > -1) {
				rooms[wIndex][lIndex].west = new Room();
				(*rooms[wIndex][lIndex].west) = rooms[wIndex - 1][lIndex];
			}
			else {
				rooms[wIndex][lIndex].west = nullptr;
			}
			//North
			if (lIndex - 1 > -1) {
				rooms[wIndex][lIndex].north = new Room();
				(*rooms[wIndex][lIndex].north) = rooms[wIndex][lIndex - 1];
			}
			else {
				rooms[wIndex][lIndex].north = nullptr;
			}
			//South
			if (lIndex + 1 < length) {
				rooms[wIndex][lIndex].south = new Room();
				(*rooms[wIndex][lIndex].south) = rooms[wIndex][lIndex + 1];
			}
			else {
				rooms[wIndex][lIndex].south = nullptr;
			}
		}

	}
}

void Floor::createRooms()
{
	rooms.reserve(width);
	//Fill grid with rooms
	for (int wIndex = 0; wIndex < width; wIndex++)
	{
		vector<Room> temp;
		temp.reserve(length);
		for (int lIndex = 0; lIndex < length; lIndex++) {
			temp.push_back(Room(wIndex, lIndex));
		}

		rooms.push_back(temp);
	}
}
