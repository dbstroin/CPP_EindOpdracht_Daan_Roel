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

Room::Room(int x, int y)
{
	_x = x;
	_y = y;
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
	if (visited) {
		type = "N";
	}
	else
	{
		type = ".";
	}
	cout << type;
}

void Room::AddToys()
{
}

int Room::get_x() {
	return _x;
}

void Room::AddEnemies(Enemy e)
{

}

