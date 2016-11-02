#include "stdafx.h"
#include "Player.h"


Player::Player()
{
}


Player::~Player()
{
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