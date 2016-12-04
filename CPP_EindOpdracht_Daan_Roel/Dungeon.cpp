#include "stdafx.h"
#include "Dungeon.h"
#include "Item.h"
#include "Talisman.h"
#include "SmallPotion.h"
#include "Enemy.h"
#include <iostream>
#include <string>
#include <sstream>

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
	fillEncounterableItems();
	spawnPlayer();
}

void Dungeon::spawnPlayer() {

	int randomX = getRandom(0, width - 1);
	int randomY = (0, length - 1);
	floors[currFloor].startFloor(randomX, randomY);
}

void Dungeon::play() {
	floors[currFloor].drawMap();

	tryNextFloor();
	if (finished) {
		for each (Floor floor in floors) floor.clear();
		for each (Item* i in encounterableItems) delete i;
		return;
	}
	tryEncounterItem();
	tryEncounterEnemy();
	while(!tryMove());
}


void Dungeon::tryEncounterItem() {
	int encounterChance = encounterableItems.size() * 2;
	//int encounterChance = possibleEnemies.size() - 1; // = always encounter item

	int randomItem = getRandom(0, encounterChance);


	if (randomItem < encounterableItems.size()) {
		vector<Item*> v = player->getItems();
		if (std::find(v.begin(), v.end(), encounterableItems[randomItem]) == v.end()) 
		{
			cout << "You found a " << encounterableItems[randomItem]->name << "! It was added to your inventory" << endl << endl;
			player->addItem(encounterableItems[randomItem]);
		}
	}
}

void Dungeon::tryEncounterEnemy() {
	Enemy* enemy = floors[currFloor].tryEncounterEnemy();
	if (enemy != NULL) {
		cout << "You encountered a: " << enemy->name << endl;
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
			cout << item << ": " << items[item]->name << endl;	
		}
		cout << items.size() << ": " << "Cancel" << endl;

		int answer = getAnswer(items.size() + 1);
		if (answer != items.size()) {
			if (items[answer]->name == "Talisman") {
				floors[currFloor].useTalisman();
			}
			else if (items[answer]->name == "Small Potion") {
				player->addHealth(10);
				player->deleteItem(items[answer]);			
			}
		}
	}
	else {
		cout << "You currently don't have any items" << endl;
	}
}

bool Dungeon::tryMove() 
{
	vector<string> options = floors[currFloor].getDirectionOptions();
	cout << "These are your current options, what would you like to do?" << endl;

	int i = 0;
	while (i < options.size())
	{
		cout << i <<": Go " << options[i] << endl;
		i++;
	}
	cout << i << ": Use an item" << endl << endl;
	int answer = getAnswer(options.size() + 1);
	if (answer == i) {
		tryItems();
		return false;
	}
	else {
		floors[currFloor].movePlayer(answer, options);
		return true;
	}
	
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

void Dungeon::fillEncounterableItems() {
	encounterableItems.push_back(new SmallPotion(1));
	for each (Item* i in encounterableItems)
	{
		i->setName();
	}
}

int Dungeon::getAnswer(int amountOfOptions) {
	string line;
	double d;
	int answer = -1;
	while (getline(std::cin, line))
	{
		stringstream ss(line);
		if (ss >> d)
		{
			if (ss.eof())
			{   
				answer = std::stoi(line);
				if (answer < amountOfOptions && answer >= 0) {
					break;
				}
			}
		}
		cout << "invalid input, try again" << endl;
	}
	return answer;
}