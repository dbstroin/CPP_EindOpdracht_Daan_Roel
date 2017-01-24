#include "stdafx.h"
#include "Grenade.h"


Grenade::Grenade()
{
}


Grenade::~Grenade()
{
}

void Grenade::useItem(Player * p)
{
	p->addDamage(1);
}

void Grenade::setName()
{
	name = "Grenade";
}
