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

	void loadPlayer();

	void newPlayer();

	void getHit(int damage);

	void setX(int ix);

	void setY(int iy);

	int getY();

	int getX();

	int getDamage();

	void addItem(Item*);

	void addExperience(int amount);

	vector<Item*> getItems();



private:
	int x;
	int y;
	string name;
	int level;
	int experience;
	int damage;
	int defense;
	int maxHealth;
	int currHealth;
	vector<Item*> items;

};

