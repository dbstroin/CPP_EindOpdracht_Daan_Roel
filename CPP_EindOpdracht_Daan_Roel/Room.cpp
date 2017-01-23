#include "stdafx.h"
#include "Room.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

Room::Room()
{
}

Room::~Room()
{
}

Room::Room(int x, int y, string t)
{
	searchVisited = false;
	visiting = false;
	visited = false;
	_x = x;
	_y = y;
	type = t;
}

int Room::GetCombinedHitPoints()
{
	int hitPoints = enemy.hitPoints;

	if (hitPoints != NULL) {
		return hitPoints;
	}
	else {
		return 1;
	}
}

void Room::Draw()
{
	if (north == nullptr && south == nullptr && east == nullptr && west == nullptr) cout << ".";
	else if (visiting) cout << 'P';
	else if (visited || showAllRooms) cout << type;
	else cout << ".";
}

void Room::AddToys()
{
}

void Room::setType(string t)
{
	type = t;
}

string Room::getType() {
	return type;
}

void Room::playerVisits()
{
	visited = true;
	visiting = true;
}

void Room::playerLeaves()
{
	visiting = false;
}
void Room::AddEnemy(vector<Enemy> e)
{
	// pak een RANDOM int
	int randomIndex = 0;
	
	Enemy enemyToAdd = e[randomIndex];
	//int i = 0; // voor testen
}



vector<string> Room::getAvailableDirections() {
	vector<string> temp;
	temp.reserve(4);
	if (north != nullptr) {
		temp.push_back("north");
	}
	if (east != nullptr) {
		temp.push_back("east");
	}
	if (south != nullptr) {
		temp.push_back("south");
	}
	if (west != nullptr) {
		temp.push_back("west");
	}
	return temp;
}


#pragma region GettersSetters
Room* Room::getEast() {
	return east;
}

void Room::setEast(Room* r) {
	east = r;
}

void Room::setNorth(Room* r) {
	north = r;
}

Room* Room::getNorth() {
	return north;
}

Room* Room::getWest() {
	return west;
}

void Room::setWest(Room* r) {
	west = r;
}

Room* Room::getSouth() {
	return south;
}

void Room::setSouth(Room* r) {
	south = r;
}

void Room::setSearchVisited(bool i) {
	searchVisited = i;
}

bool Room::getSearchVisited() {
	return searchVisited;
}



vector<Room*> Room::getAdjacentRooms()
{
	vector<Room*> temp;
	temp.reserve(4);
	if (north != nullptr) {
		temp.push_back(north);
	}
	if (east != nullptr) {
		temp.push_back(east);
	}
	if (south != nullptr) {
		temp.push_back(south);
	}
	if (west != nullptr) {
		temp.push_back(west);
	}
	return temp;
}
void Room::setRandomBeschrijving()
{
	beschrijving = "Beschrijving: ";
	int random = getRandom(0, 3);
	switch (random) {
	case 0: 
		beschrijving += "In de hoek van de kamer staat een stoel waarop een skelet zit dat niet beweegt.";
		break;
	case 1:
		beschrijving += "Aan het plafond hangt een knipperende lamp waardoor het moeilijk is om rond te kijken.";
		break;
	case 2:
		beschrijving += "Op de vloer bevindt zich een grote hoeveelheid mos. Er is hier waarschijnlijk lang niemand meer geweest.";
		break;
	case 3:
		beschrijving += "Aan de Oostelijke muur zie je een raam naar buiten. Maar het lijkt niet dat hier iets of iemand doorheen past.";
		break;
	}
}
#pragma endregion
