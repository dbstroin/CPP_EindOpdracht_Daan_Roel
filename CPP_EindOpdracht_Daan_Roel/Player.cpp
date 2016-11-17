#include "stdafx.h"
#include "Player.h"
#include <random>
#include <ctime>
#include <string>

Player::Player()
{
}


Player::~Player()
{
}

void Player::loadPlayer() {

}

void Player::newPlayer() {
	name = "rel";
	level = 1;
	experience = 0;
	damage = 10;
	defense = 10;
	maxHealth = 1000;
	currHealth = 100;
}

void Player::getHit(int damage) {
	default_random_engine gen;
	gen.seed(time(0));

	uniform_int_distribution<int> distribution4(0, 100);
	int random = distribution4(gen);

	if (random > defense) {
		currHealth = currHealth - damage;
		cout << "You got hit for " << damage << " damage!" << endl;
	}
	else {
		cout << "You blocked the enemies attack!" << endl;
	}
}

void Player::addItem(Item * i) {
	items.push_back(i);
}

void Player::addExperience(int amount) {
	int expToNextlvl = 10;
	experience = experience + amount;
	cout << "Experience gained: " << amount << endl;
	if (experience > expToNextlvl) {
		experience = experience - expToNextlvl;
		level++;
		cout << "You leveled up! You are now level " << level << endl;
	}
	cout << "Current experience: " << experience << "/" << expToNextlvl << endl;
}

vector<Item*> Player::getItems() {
	return items;
}

void Player::setX(int ix) {
	x = ix;
}

void Player::setY(int iy) {
	y = iy;
}

int Player::getY() {
	return y;
}

int Player::getX() {
	return x;
}

int Player::getDamage() {
	return damage;
}