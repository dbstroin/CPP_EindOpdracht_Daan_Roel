#pragma once
#include "Item.h"

class Talisman : Item
{
public:
	Talisman();
	~Talisman();
	Talisman(std::string nameIn, int amountIn) : Item(nameIn, amountIn) {};
	bool useItem();
};

