#include "stdafx.h"
#include "Floor.h"
#include <random>
#include <ctime>

vector<vector<Room>> rooms;

Floor::Floor()
{
}

Floor::Floor(int l, int w, int lev)
{
	length = l;
	width = w;
	level = lev;

	playerx = 0;
	playery = 0;
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

				rooms[wIndex][lIndex].east = &rooms[wIndex + 1][lIndex];
			}
			else {
				rooms[wIndex][lIndex].east = nullptr;
			}
			//West
			if (wIndex - 1 > -1) {
	
				rooms[wIndex][lIndex].west = &rooms[wIndex - 1][lIndex];
			}
			else {
				rooms[wIndex][lIndex].west = nullptr;
			}
			//North
			if (lIndex - 1 > -1) {

				rooms[wIndex][lIndex].north = &rooms[wIndex][lIndex - 1];
			}
			else {
				rooms[wIndex][lIndex].north = nullptr;
			}
			//South
			if (lIndex + 1 < length) {

				rooms[wIndex][lIndex].south = &rooms[wIndex][lIndex + 1];
			}
			else {
				rooms[wIndex][lIndex].south = nullptr;
			}
		}

	}
	//rooms[playerx][playery].east->playerVisits();
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
			Room r = Room(wIndex, lIndex, "N");
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

	rooms[randomx][randomy].setType("H");

}

void Floor::drawMap()
{
	rooms[playerx][playery].east->playerVisits();
	for (int lIndex = 0; lIndex < length; lIndex++) {
		cout << "   ";

		for (int wIndex = 0; wIndex < width; wIndex++) {
			if (rooms[wIndex][lIndex].north != nullptr) {
				cout << "| ";
			}
		}

		cout << endl;
		cout << "   ";

		for (int wIndex = 0; wIndex < width; wIndex++) {
			rooms[wIndex][lIndex].Draw();
			if (rooms[wIndex][lIndex].east != nullptr) {
				cout << "-";
			}
		}
		cout << endl;
	}
	cout << endl;
}

void Floor::startFloor(int startx, int starty)
{
	playerx = startx;
	playery = starty;
	rooms[startx][starty].playerVisits();
	createStairs(startx, starty);
	drawMap();
}

vector<string> Floor::getDirectionOptions()
{
	return rooms[playerx][playery].getAvailableDirections();
}

void Floor::movePlayer(int direction, vector<string> options) 
{
	rooms[playerx][playery].playerLeaves();
	if (options[direction] == "north") {
		rooms[playerx][playery].north->playerVisits();
		playery--;
	}
	if (options[direction] == "east") {
		rooms[playerx][playery].east->playerVisits();
		playerx++;
	}
	if (options[direction] == "south") {
		rooms[playerx][playery].south->playerVisits();
		playery++;
	}
	if (options[direction] == "west") {
		rooms[playerx][playery].west->playerVisits();
		playerx--;
	}
}