#pragma once
#include <iostream>
#include <list>
#include "Floor.h"

using namespace std;

class Dungeon
{
public:
	Dungeon();
	~Dungeon();
private:
	int length;
	int width;
	int layers;
	list<Floor> floors;
};

