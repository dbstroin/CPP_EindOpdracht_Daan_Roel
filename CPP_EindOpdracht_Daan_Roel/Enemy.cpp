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
	default_random_engine gen;
	gen.seed(time(0));

	uniform_int_distribution<int> distribution4(0, 100);
	int random = distribution4(gen);

	if (random > blockChance) {
		hitPoints = hitPoints - damage;
		cout << "You dealt " << damage << " damage to the " << name << "!" << endl;
	}
	else {
		cout << "the " << name << " blocked your attack!" << endl;
	}
}

int Enemy::getDamage() {
	default_random_engine gene;
	gene.seed(time(0));

	uniform_int_distribution<int> distribution5(minDamage, maxDamage);
	int damage = distribution5(gene);
	return damage;
}