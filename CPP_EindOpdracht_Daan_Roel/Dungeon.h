#pragma once
#include <iostream>
#include <list>
#include "Floor.h"
#include "Room.h"


using namespace std;

class Dungeon
{
public:
	Dungeon(int width, int length, int floors);
	Dungeon();
	~Dungeon();
	void play();
	int askPlayerWhatSide(vector<string> options);
	vector<Floor> floors;
private:
	int length;
	int width;
	int layers;
	int currFloor;
};

