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
	if (visiting) cout << 'P';
	else if (visited) cout << type;
	else cout << type; //".";
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

void Room::playerVisits()
{
	visited = true;
	visiting = true;
	type = 'P';
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


