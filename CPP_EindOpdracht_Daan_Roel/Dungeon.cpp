#include "stdafx.h"
#include "Dungeon.h"
#include <list>
#include <iostream>
#include <string>

using namespace std;

Dungeon::Dungeon(int w, int l, int f)
{
	currFloor = 0;
	width = w;
	length = l;
	layers = f;
	for (int level = 0; level < layers; level++) {
		floors.push_back(AddFloor(width, length, level));
	}
}

Dungeon::Dungeon()
{
}

Dungeon::~Dungeon()
{
}

void Dungeon::play() {
	floors[currFloor].startFloor(0, 0);
	vector<string> options = floors[currFloor].getDirectionOptions();
	int answer = askPlayerWhatSide(options);
	floors[currFloor].movePlayer(answer, options);
}

Floor Dungeon::AddFloor(int width, int height, int level)
{
	Floor floor(width, height, level);
	return floor;
}

int Dungeon::askPlayerWhatSide(vector<string> options) 
{
	cout << "You can go in " << options.size() << " directions" << endl;
	cout << "Choose an option below" << endl;
	for (int i = 0; i < options.size(); i++)
	{
		cout << i + 1 <<": " << options[i] << endl;
	}
	int answer;
	cin >> answer;
	return answer-1;
}