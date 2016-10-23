#pragma once
#include <iostream>

using namespace std;

class Item
{
public:
	Item();
	~Item();

	bool useItem();
private:
	string name;
	int amount;
};

