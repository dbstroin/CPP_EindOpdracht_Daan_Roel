#pragma once
#include <iostream>
#include "Player.h"

using namespace std;

class Player;

class Item
{
public:
	Item();
	~Item();
	Item(int amountIn);
	string name;
	int amount;

	virtual void useItem(Player* p);
	virtual void setName();

protected:

};

