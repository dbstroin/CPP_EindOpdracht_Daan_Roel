#pragma once
#include "Item.h"

class Talisman : public Item
{
public:
	Talisman();
	~Talisman();
	Talisman(int amountIn) : Item(amountIn) {};
	bool useItem();
	void setName();
};

