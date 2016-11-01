#pragma once
#include <iostream>
#include <List>
#include "Item.h"

using namespace std;

class Player
{
public:
	Player();
	~Player();

private:
	string name;
	int level;
	int experience;
	int hitPoints;
	int damage;
	int defense;

	list<Item> items;
};

