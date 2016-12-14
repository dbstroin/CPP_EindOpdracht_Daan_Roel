#include "stdafx.h"
#include "LargePotion.h"


LargePotion::LargePotion()
{
}


LargePotion::~LargePotion()
{
}

void LargePotion::useItem(Player * p)
{
	p->addHealth(100);
}

void LargePotion::setName()
{
	name = "Large Potion";
}
