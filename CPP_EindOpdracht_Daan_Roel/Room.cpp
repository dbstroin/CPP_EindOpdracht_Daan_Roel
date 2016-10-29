#include "stdafx.h"
#include "Room.h"


Room::Room()
{
}


Room::~Room()
{
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

void Room::AddToys()
{
}

void Room::AddEnemies()
{
}

void Room::AddDoors()
{
}
