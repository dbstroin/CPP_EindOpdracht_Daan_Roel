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
	int hitPoints = enemy.hitPoints;

	if (hitPoints != NULL) {
		return hitPoints;
	}
	else {
		return 0;
	}
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

void Room::AddEnemy(vector<Enemy> e)
{
	int randomIndex = rand() % e.size();
	
	// kopie maken van de enemy op die random index doe ik vanavond ...
	// enemy =
}

