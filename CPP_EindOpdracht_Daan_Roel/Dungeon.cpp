#include "stdafx.h"
#include "Dungeon.h"
#include "Item.h"
#include "Talisman.h"
#include "Enemy.h"
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

Dungeon::Dungeon(int w, int l, int f, Player* p)
{
	finished = false;
	player = p;
	currFloor = 0;
	width = w;
	length = l;
	layers = f;
	for (int level = 0; level < layers; level++) {
		Floor* f = new Floor(width, length, level, player);
		floors.push_back((*f));
		delete f;
	}
	spawnPlayer();
	Item* talisman = new Talisman(1);
	talisman->setName();
	//player->addItem(talisman);
	delete talisman;
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
		for each (Floor floor in floors) floor.clear();
		return;
	}
	tryEncounterEnemy();
	tryItems();
	tryMove();
}

void Dungeon::tryEncounterEnemy() {
	Enemy* enemy = floors[currFloor].tryEncounterEnemy();
	if (enemy != NULL) {
		cout << "You encountered: " << enemy->name << endl;
		Fight(enemy);
	}
	cout << endl;
}

void Dungeon::Fight(Enemy* enemy) {
	if (enemy->hitPoints > 0) {
		cout << "What would you like to do?" << endl;
		cout << "0: Attack" << endl;
		cout << "1: Run" << endl;
		cout << "2: Use Item" << endl;

		bool correct = false;
		int answer;
		while (!correct) {
			cin.clear();
			cin >> answer;
			if (answer < 3 && answer >= 0) {
				correct = true;
			}
		}
		switch (answer) {
		case 0: //Attack
			enemy->getHit(player->getDamage());
			if (enemy->hitPoints > 0) {
				player->getHit(enemy->getDamage());
			}
			else { //Enemy Killed
				floors[currFloor].deleteEnemy(enemy);
				cout << "You killed the " << enemy->name << "!" << endl;
				player->addExperience(enemy->level);
				delete enemy;
			}
			break;
		case 1: //Run
			cout << "You ran away safely" << endl;
			return;
			break;
		case 2: //Use Item
			tryItems();
			break;
		}

		cout << endl;
		Fight(enemy);
	}
}

void Dungeon::tryItems() {
	vector<Item*> items = player->getItems();
	if (items.size() > 0) {
		cout << "You can use one of the following items:" << endl;
		for (int item = 0; item < items.size(); item++) {
			cout << item << ": " << items[item]->getName() << endl;	
		}
		cout << items.size() << ": " << "Cancel" << endl;

		int answer = getAnswer(items.size() + 1);
		if(answer != items.size()) floors[currFloor].useItem(items[answer]);
	}
	else {
		cout << "You currently don't have any items" << endl;
	}
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
	int answer = getAnswer(options.size());
	
	floors[currFloor].movePlayer(answer, options);
	cout << endl;
}

void Dungeon::tryNextFloor() {
	if (floors[currFloor].getIfOnPlayerOnStairs()) {
		cout << "You have found the stairs do you want to move to the next floor? " << endl;
		cout << "0: yes" << endl;
		cout << "1: no" << endl;
		cout << endl;
		bool correct = false;
		int answer = getAnswer(2);
		if (answer == 0) {
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
	}
	cout << endl;
}

int Dungeon::getAnswer(int amountOfOptions) {
	bool correct = false;
	int answer;
	while (!correct) {
		cin.clear();
		cin >> answer;
		if (answer < amountOfOptions && answer >= 0) {
			correct = true;
		}
	}
	return answer;
}