#include "stdafx.h"
#include "AttackUp.h"


AttackUp::AttackUp()
{
}


AttackUp::~AttackUp()
{
}

void AttackUp::useItem(Player * p)
{
	p->addDamage(1);
}

void AttackUp::setName()
{
	name = "Attack Up";
}
