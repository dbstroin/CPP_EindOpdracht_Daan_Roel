#include "stdafx.h"
#include "Enemy.h"
#include <random>
#include <ctime>
#include <iostream>
#include <string>

Enemy::Enemy()
{
}


Enemy::~Enemy()
{
}

void Enemy::getHit(int damage) {
	int random = getRandom(0, 100);

	if (random > blockChance) {
		hitPoints = hitPoints - damage;
		if (hitPoints < 0) hitPoints = 0;
		cout << "You dealt " << damage << " damage to the " << name << "!" << endl;
	}
	else {
		cout << "The " << name << " blocked your attack!" << endl;
	}
	cout << "The " << name << " has " << hitPoints << " health left." << endl;
}

int Enemy::getDamage() {
	int damage = getRandom(minDamage, maxDamage);
	return damage;
}