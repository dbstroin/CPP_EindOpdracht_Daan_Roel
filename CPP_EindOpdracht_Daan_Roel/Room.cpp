#include "stdafx.h"
#include "Room.h"
#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <ctime>

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
	int hitPoints = enemy->hitPoints;

	if (hitPoints != NULL) {
		return hitPoints;
	}
	else {
		return 0;
	}
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

void Room::AddEnemy(vector<Enemy *> e)
{
	bool randomSet = false;
	int randomIndex = 0;

	while (!randomSet) {
		default_random_engine generator;
		generator.seed(time(0));

		uniform_int_distribution<int> distribution1(0, 99);
		randomIndex = distribution1(generator);

		if (randomIndex < 50) {
			uniform_int_distribution<int> distribution2(0, e.size() - 1);
			randomIndex = distribution2(generator);

			enemy = e[randomIndex];
		}
		randomSet = true;
	}
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

bool Room::setSearchVisited() {
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
bool Room::hasEnemy() {
	if (enemy != nullptr) {
		return true;
	}
	else return false;
}

Enemy * Room::getEnemy()
{
	return enemy;
}
