#include "stdafx.h"
#include "MediumPotion.h"
#include "Player.h"

MediumPotion::MediumPotion()
{
}


MediumPotion::~MediumPotion()
{
}

void MediumPotion::useItem(Player * p)
{
	p->addHealth(50);
}

void MediumPotion::setName()
{
	name = "Medium Potion";
}
