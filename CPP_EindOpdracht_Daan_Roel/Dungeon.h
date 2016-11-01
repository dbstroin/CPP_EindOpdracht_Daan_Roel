#pragma once
#include <iostream>
#include <list>
#include "Floor.h"


using namespace std;

class Dungeon
{
public:
	Dungeon(int width, int length, int floors);
	Dungeon();
	~Dungeon();
	void play();
	Floor AddFloor(int width, int length, int level);
	int askPlayerWhatSide(vector<string> options);
private:
	int length;
	int width;
	int layers;
	int currFloor;
	vector<Floor> floors;
};

