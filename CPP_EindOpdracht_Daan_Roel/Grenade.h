#pragma once
#include "Item.h"

class Grenade : public Item
{
public:
	Grenade();
	~Grenade();
	Grenade(int amountIn) : Item(amountIn) {};
	void useItem(Player* p);
	void setName();
};