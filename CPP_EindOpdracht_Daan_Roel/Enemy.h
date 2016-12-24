#pragma once
#include <iostream>
#include "Globalfunc.h"

using namespace std;

class Enemy
{
public:
	Enemy();
	~Enemy();
	void getHit(int damage);
	int getDamage();
	string name;
	int level;
	int hitPoints;
	int hitChance;
	int hitAmount;
	int minDamage;
	int maxDamage;
	int blockChance;
private:
};

