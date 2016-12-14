#pragma once
#include "Item.h"

class SmallPotion : public Item
{
public:
	SmallPotion();
	~SmallPotion();
	SmallPotion(int amountIn) : Item(amountIn) {};
	void useItem(Player* p);
	void setName();
};

