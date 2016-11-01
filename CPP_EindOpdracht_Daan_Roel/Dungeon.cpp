#include "stdafx.h"
#include "Dungeon.h"
#include <list>
#include <iostream>
#include <string>
#include <random>
#include <ctime>

using namespace std;

Dungeon::Dungeon()
{
}

Dungeon::~Dungeon()
{
}

Dungeon::Dungeon(int w, int l, int f)
{
	currFloor = 0;
	width = w;
	length = l;
	layers = f;
	for (int level = 0; level < layers; level++) {
		Floor* f = new Floor(width, length, level);
		floors.push_back((*f));
		delete f;
	}
	finished = false;
	spawnPlayer();
}

void Dungeon::spawnPlayer() {
	default_random_engine generator;
	generator.seed(time(0));

	uniform_int_distribution<int> distribution1(0, width - 1);
	int randomX = distribution1(generator);
	uniform_int_distribution<int> distribution2(0, length - 1);
	int randomY = distribution2(generator);
	floors[currFloor].startFloor(randomX, randomY);
}

void Dungeon::play() {
	floors[currFloor].drawMap();

	tryNextFloor();
	if (finished) {
		for each (Floor floor in floors)
		{
			floor.clear();
		}
		return;
	}
	tryMove();
}

void Dungeon::tryMove() 
{
	vector<string> options = floors[currFloor].getDirectionOptions();
	cout << "There are " << options.size() << " available directions." << endl;
	cout << "Choose an option below: " << endl;
	for (int i = 0; i < options.size(); i++)
	{
		cout << i <<": " << options[i] << endl;
	}
	cout << endl;
	bool correct = false;
	int answer;
	while (!correct) {
		cin.clear();
		cin >> answer;
		if (answer < options.size() && answer >= 0) {
			correct = true;
		}
	}
	
	floors[currFloor].movePlayer(answer, options);
}

void Dungeon::tryNextFloor() {
	if (floors[currFloor].getIfOnPlayerOnStairs()) {
		cout << "You have found the stairs do you want to move to the next floor? " << endl;
		cout << "0: yes" << endl;
		cout << "1: no" << endl;
		cout << endl;
		bool correct = false;
		int answer;
		while (!correct) {
			cin.clear();
			cin >> answer;
			if (answer == 0) {
				correct = true;
				currFloor++;
				if (currFloor < floors.size()) {
					spawnPlayer();
					floors[currFloor].drawMap();
				}
				else {
					cout << "You succesfully exited the dungeon, Congratulations!" << endl;
					getchar(); getchar();
					finished = true;
				}
			}
			else if (answer == 1) {
				correct = true;
			}
		}
	}
}