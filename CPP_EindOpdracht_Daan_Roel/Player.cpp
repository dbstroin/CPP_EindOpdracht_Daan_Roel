#include "stdafx.h"
#include "Player.h"


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


void Player::addItem(Item * i) {
	items.push_back(i);
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