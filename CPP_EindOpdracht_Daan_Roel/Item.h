#pragma once
#include <iostream>

using namespace std;

class Item
{
public:
	Item();
	~Item();
	Item(int amountIn);
	string getName();

	virtual bool useItem();
	virtual void setName();

protected:
	string name;
	int amount;
};

