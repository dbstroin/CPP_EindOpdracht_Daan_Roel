#pragma once
#include "Item.h"

class MediumPotion : public Item
{
public:
	MediumPotion();
	~MediumPotion();
	MediumPotion(int amountIn) : Item(amountIn) {};
	void useItem(Player* p);
	void setName();
};

