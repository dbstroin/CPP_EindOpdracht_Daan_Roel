#include "stdafx.h"
#include "DefenseUp.h"


DefenseUp::DefenseUp()
{
}


DefenseUp::~DefenseUp()
{
}

void DefenseUp::useItem(Player * p)
{
	p->addDefense(1);
}

void DefenseUp::setName()
{
	name = "Defense Up";
}
