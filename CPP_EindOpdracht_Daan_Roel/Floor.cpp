#include "stdafx.h"
#include "Floor.h"
#include <random>
#include <ctime>

Floor::Floor()
{
}

Floor::~Floor()
{
}

Floor::Floor(int l, int w, int lev)
{
	length = l;
	width = w;
	level = lev;

	createRooms();
	createEdges();
}


void Floor::createEdges()
{
	//Connect rooms on ALL sides
	for (int wIndex = 0; wIndex < width; wIndex++)
	{
		for (int lIndex = 0; lIndex < length; lIndex++) {
			//East
			if (wIndex + 1 < width) {

				rooms[wIndex][lIndex]->setEast(rooms[wIndex + 1][lIndex]);
			}
			//West
			if (wIndex - 1 > -1) {
	
				rooms[wIndex][lIndex]->setWest(rooms[wIndex - 1][lIndex]);
			}
			//North
			if (lIndex - 1 > -1) {

				rooms[wIndex][lIndex]->setNorth(rooms[wIndex][lIndex - 1]);
			}
			//South
			if (lIndex + 1 < length) {

				rooms[wIndex][lIndex]->setSouth(rooms[wIndex][lIndex + 1]);
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
		vector<Room*> temp;
		temp.reserve(length);
		for (int lIndex = 0; lIndex < length; lIndex++) {
			Room* r = new Room(wIndex, lIndex, "N");
			temp.push_back(r);
		}

		rooms.push_back(temp);
	}
}

void Floor::createStairs(int playerx, int playery) {
	bool randomSet = false;
	int randomx;
	int randomy;

	while (!randomSet) {
		default_random_engine generator;
		generator.seed(time(0));

		uniform_int_distribution<int> distribution1(0, width-1);
		randomx =  distribution1(generator);
		uniform_int_distribution<int> distribution2(0, length - 1);
		randomy = distribution2(generator);

		if (randomx == playerx && randomy == playery);
		else {
			randomSet = true;
		}
	}

	rooms[randomx][randomy]->setType("H");

}

void Floor::drawMap()
{
	for (int lIndex = 0; lIndex < length; lIndex++) {
		cout << "   ";

		for (int wIndex = 0; wIndex < width; wIndex++) {
			if (rooms[wIndex][lIndex]->getNorth() != nullptr) {
				cout << "| ";
			}
		}

		cout << endl;
		cout << "   ";

		for (int wIndex = 0; wIndex < width; wIndex++) {
			rooms[wIndex][lIndex]->Draw();
			if (rooms[wIndex][lIndex]->getEast() != nullptr) {
				cout << "-";
			}
		}
		cout << endl;
	}
	cout << endl;
}

void Floor::startFloor(int startx, int starty)
{
	playerX = startx;
	playerY = starty;
	rooms[startx][starty]->playerVisits();
	createStairs(startx, starty);
}

vector<string> Floor::getDirectionOptions()
{
	return rooms[playerX][playerY]->getAvailableDirections();
}

bool Floor::getIfOnPlayerOnStairs() {
	if (rooms[playerX][playerY]->getType() == "H") return true;
	else return false;
}

void Floor::movePlayer(int direction, vector<string> options) 
{
	rooms[playerX][playerY]->playerLeaves();
	if (options[direction] == "north") {
		rooms[playerX][playerY]->getNorth()->playerVisits();
		playerY--;
	}
	if (options[direction] == "east") {
		rooms[playerX][playerY]->getEast()->playerVisits();
		playerX++;
	}
	if (options[direction] == "south") {
		rooms[playerX][playerY]->getSouth()->playerVisits();
		playerY++;
	}
	if (options[direction] == "west") {
		rooms[playerX][playerY]->getWest()->playerVisits();
		playerX--;
	}
}