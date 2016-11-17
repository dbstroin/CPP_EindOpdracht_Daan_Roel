#include "stdafx.h"
#include "Item.h"


Item::Item()
{
}


Item::~Item()
{
}

Item::Item(int amountIn)
{
	amount = amountIn;
}

string Item::getName()
{
	return name;
}

bool Item::useItem()
{
	return false;
}

void Item::setName()
{
}

