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
	ifstream file;
	file.open("monsters.txt");

	string line = "";
	if (file.is_open()) {
		while (!file.eof()) {
			getline(file, line);

			if ()

		}
	}
	file.close();

}

