#pragma once
#include <iostream>

using namespace std;

class Item
{
public:
	Item();
	~Item();
	Item(int amountIn);
	string name;
	int amount;

	virtual void useItem();
	virtual void setName();

protected:

};

