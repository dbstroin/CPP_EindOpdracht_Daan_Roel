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
}

void Room::AddToys()
{
}

void Room::AddEnemies()
{
	//ifstream file;
	//file.open("monsters.txt");

	//string line = "";
	//if (file.is_open()) {
	//	while (!file.eof()) {
	//		getline(file, line);

	//	}
	//}
	//file.close();

}

