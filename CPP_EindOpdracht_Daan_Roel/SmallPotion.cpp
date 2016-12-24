#include "stdafx.h"
#include "SmallPotion.h"


SmallPotion::SmallPotion()
{
}


SmallPotion::~SmallPotion()
{
}

void SmallPotion::useItem(Player * p)
{
	p->addHealth(10);
}

void SmallPotion::setName()
{
	name = "Small Potion";
}
