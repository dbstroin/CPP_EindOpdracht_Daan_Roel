#pragma once
#include <iostream>

using namespace std;

class Enemy
{
public:
	Enemy();
	~Enemy();
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

