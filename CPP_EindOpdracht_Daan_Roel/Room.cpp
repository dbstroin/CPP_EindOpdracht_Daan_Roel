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
	visiting = false;
	visited = false;
	_x = x;
	_y = y;
	type = t;
}

int Room::GetCombinedHitPoints()
{
	int hitPoints = 0;
	for each (Enemy enemy in enemies)
	{
		//hitPoints += enemy.getHitPoints();
	}
	return hitPoints;
}

void Room::Draw()
{
	if (visiting == true) {
		cout << 'P';
	}
	else if (visited == true) cout << type;
	else cout << ".";
}

void Room::AddToys()
{
}

void Room::AddEnemies(Enemy e)
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
#pragma endregion
