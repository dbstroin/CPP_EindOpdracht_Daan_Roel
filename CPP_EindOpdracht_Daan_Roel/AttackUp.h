#pragma once
#include "Item.h"

class AttackUp : public Item
{
public:
	AttackUp();
	~AttackUp();
	AttackUp(int amountIn) : Item(amountIn) {};
	void useItem(Player* p);
	void setName();
};

