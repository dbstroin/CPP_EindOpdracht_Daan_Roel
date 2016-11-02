#pragma once
#include <iostream>
#include <List>
#include "Item.h"
#include <vector>

using namespace std;

class Player
{
public:
	Player();
	~Player();

	void setX(int ix);

	void setY(int iy);

	int getY();

	int getX();

	void addItem(Item*);

	vector<Item*> getItems();



private:
	int x;
	int y;
	string name;
	int level;
	int experience;
	int hitPoints;
	int damage;
	int defense;
	int maxHealth;
	int currHealth;
	vector<Item*> items;

};

