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
	int hitPoints;
	for each (Enemy enemy in enemies)
	{
		hitPoints += enemy.hitPoints;
	}
	return hitPoints;
}
