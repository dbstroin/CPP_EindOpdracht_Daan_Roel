#pragma once
#include "Item.h"

class DefenseUp : public Item
{
public:
	DefenseUp();
	~DefenseUp();
	DefenseUp(int amountIn) : Item(amountIn) {};
	void useItem(Player* p);
	void setName();
};

