#pragma once
#include <iostream>
#include <List>
#include <fstream>
#include "Item.h"
#include "string"
#include <vector>
#include "Globalfunc.h"

using namespace std;

class Item;

class Player
{
public:
	Player();
	~Player();

	void savePlayer();

	void loadPlayer(std::string playerName);

	void newPlayer();

	void getHit(int damage);

	void setX(int ix);

	void setY(int iy);

	int getY();

	int getX();

	int getDamage();

	void addItem(Item*);

	void addExperience(int amount);

	void addHealth(int amount);

	void addDamage(int amount);

	void addDefense(int amount);

	void deleteItem(Item * item);

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

