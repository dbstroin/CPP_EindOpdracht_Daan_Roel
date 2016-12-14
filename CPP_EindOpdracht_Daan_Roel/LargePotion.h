#pragma once
#include "Item.h"

class LargePotion : public Item
{
public:
	LargePotion();
	~LargePotion();
	LargePotion(int amountIn) : Item(amountIn) {};
	void useItem(Player* p);
	void setName();
};

