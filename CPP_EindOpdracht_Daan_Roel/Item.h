#pragma once
#include <iostream>

using namespace std;

class Item
{
public:
	Item();
	~Item();
	Item(string nameIn, int amountIn);

	virtual bool useItem();

protected:
	string name;
	int amount;
};

