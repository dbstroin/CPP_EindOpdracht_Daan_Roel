#include "stdafx.h"
#include "Dungeon.h"
#include <list>
#include <iostream>
#include <string>

using namespace std;

Dungeon::Dungeon()
{
}

Dungeon::~Dungeon()
{
}

vector<Floor> floors;

Dungeon::Dungeon(int w, int l, int f)
{
	currFloor = 0;
	width = w;
	length = l;
	layers = f;
	for (int level = 0; level < layers; level++) {
		Floor* f = new Floor(width, length, level);
		floors.push_back((*f));
	}
}

void Dungeon::play() {
	floors[currFloor].startFloor(0, 0);
	vector<string> options = floors[currFloor].getDirectionOptions();
	int answer = askPlayerWhatSide(options);
	floors[currFloor].movePlayer(answer, options);
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