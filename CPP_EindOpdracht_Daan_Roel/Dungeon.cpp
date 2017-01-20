#include "stdafx.h"
#include "Dungeon.h"
#include "Item.h"
#include "Talisman.h"
#include "SmallPotion.h"
#include "LargePotion.h"
#include "MediumPotion.h"
#include "AttackUp.h"
#include "DefenseUp.h"
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
		Floor* f = new Floor(length, width, level, player);
		floors.push_back((*f));
		delete f;
	}
	fillEncounterableItems();

	int randomX = getRandom(0, width - 1);
	int randomY = getRandom(0, length - 1);
	t = new Talisman();
	t->setName();
	player->addItem(t);
	player->setX(randomX);
	player->setY(randomY);
	setAllStairs();
	randomizeDungeon();
	spawnPlayer();

	
}

void Dungeon::spawnPlayer() {

	floors[currFloor].rooms[player->getX()][player->getY()]->playerVisits();
	floors[currFloor].drawMap();
	while (!tryBasicActions());
}

void Dungeon::randomizeDungeon() {
	for (int i = 0; i < floors.size(); i++) {
		floors[i].randomizeFloor();
	}
}

void Dungeon::setAllStairs() {
	int prevX = player->getX();
	int prevY = player->getY();
	for (int i = 0; i < floors.size(); i++)
	{
		if (i == floors.size() - 1) {
			floors[i].setBossLocation();
		}
		else {
			std::pair<int, int> pair = floors[i].setStairsToNextFloor(prevX, prevY);
			prevX = pair.first;
			prevY = pair.second;
			floors[i + 1].setStairsToPrevFloor(prevX, prevY);
		}
	}
}

void Dungeon::play() {
	floors[currFloor].drawMap();

	tryPrevFloor();
	tryNextFloor();
	tryEncounterItem();
	tryEncounterEnemy();
	if (finished) {
		for each (Floor floor in floors) floor.clear();
		for each (Item* i in encounterableItems) delete i;
		delete t;
		return;
	}
	while(!tryBasicActions());
}


void Dungeon::tryEncounterItem() {
	string roomType = floors[currFloor].rooms[player->getX()][player->getY()]->getType();
	if (roomType == "N") {
		int encounterChance = encounterableItems.size() * 2;
		//encounterChance = encounterableItems.size() - 1; // = always encounter item

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
}

void Dungeon::tryEncounterEnemy() {
	string roomType = floors[currFloor].rooms[player->getX()][player->getY()]->getType();
	if (roomType == "N") {
		Enemy* enemy = floors[currFloor].tryEncounterEnemy();
		if (enemy != NULL) {
			cout << "You encountered a: " << enemy->name << endl;
			Fight(enemy);
		}
		cout << endl;
	}
	if (roomType == "B") {
		cout << "You encountered the Dungeon Boss! It's a: " << floors[currFloor].getBoss().name << endl;
		if (Fight(&floors[currFloor].getBoss()) && player->getCurrHealth() > 0) {
			finishDungeon();
		}
	}
}

bool Dungeon::Fight(Enemy* enemy) {
	while (enemy->hitPoints > 0 && player->getCurrHealth() > 0) {
		cout << "What would you like to do?" << endl;
		cout << "0: Attack" << endl;
		cout << "1: Run" << endl;
		cout << "2: Use Item" << endl;

		int answer = getAnswer(3);

		switch (answer) {
		case 0: //Attack
			enemy->getHit(player->getDamage());
			if (enemy->hitPoints > 0) {
				player->getHit(enemy->getDamage());
				if (player->getCurrHealth() < 1) {
					playerDied();
				}
			}
			else { //Enemy Killed
				cout << "You killed the " << enemy->name << "!" << endl;
				player->addExperience(enemy->level);
				if (enemy->level != -1) {
					floors[currFloor].deleteEnemy(enemy);
				}
			}
			break;
		case 1: //Run
			cout << "You ran away safely" << endl;
			return false;
			break;
		case 2: //Use Item
			tryItems();
			break;
		}

		cout << endl;
	}
	return true;
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
			else {
				items[answer]->useItem(player);
				player->deleteItem(items[answer]);
			}
		}
	}
	else {
		cout << "You currently don't have any items" << endl;
	}
}

bool Dungeon::tryBasicActions() 
{
	cout << floors[currFloor].rooms[player->getX()][player->getY()]->getBeschrijving() << endl;
	cout << endl;
	vector<string> options = floors[currFloor].getDirectionOptions();
	cout << "These are your current options, what would you like to do?" << endl;

	int i = 0;
	while (i < options.size())
	{
		cout << i <<": Go " << options[i] << endl;
		i++;
	}

	cout << i << ": Use an item" << endl;
	cout << i + 1 << ": Show Map" << endl;
	cout << i + 2 << ": Rest" << endl;
	cout << i + 3 << ": Show Player stats" << endl;
	int answer = getAnswer(options.size() + 4);
	if (answer == i) {
		tryItems();
		return false;
	}
	else if (answer == i + 1) {
		floors[currFloor].drawMap();
		cout << endl;
		return false;
	}
	else if (answer == i + 2) {
		cout << "You started resting for a bit and restored some health" << endl;
		player->addHealth(getRandom(5, 30));
		cout << "Current Health: " << player->getCurrHealth() << "/" << player->getMaxHealth() << endl;
		cout << endl;
		return false;
	}
	else if (answer == i + 3) {
		cout << player->getName() << " player stats:" << endl;
		cout << "Level: " << player->getLevel() << endl;
		cout << "Health: " << player->getCurrHealth() << "/" << player->getMaxHealth() << endl;
		cout << "Experience: " << player->getExperience() << "/" << player->getMaxExperience() << endl;
		cout << "Damage: " << player->getDamage() << endl;
		cout << "Defense: " << player->getDefense() << endl;
		cout << endl;
		return false;
	}
	else {
		floors[currFloor].movePlayer(answer, options);
		return true;
	}
	
	cout << endl;
}

void Dungeon::tryPrevFloor() {
	if (floors[currFloor].rooms[player->getX()][player->getY()]->getType() == "D") {
		cout << "The stairs back to the previous floor is in the current room." << endl;
		cout << "Would you like to go back to the previous floor?" << endl;
		cout << "0: yes" << endl;
		cout << "1: no" << endl;
		int answer = getAnswer(2);
		if (answer == 0) {
			currFloor--;
			floors[currFloor + 1].rooms[player->getX()][player->getY()]->playerLeaves();
			floors[currFloor].rooms[player->getX()][player->getY()]->playerVisits();
			floors[currFloor].drawMap();
		}
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

			floors[currFloor - 1].rooms[player->getX()][player->getY()]->playerLeaves();
			floors[currFloor].rooms[player->getX()][player->getY()]->playerVisits();
			floors[currFloor].drawMap();
		}
	}
	cout << endl;
}

void Dungeon::finishDungeon() {
	player->savePlayer();
	cout << "You succesfully exited the dungeon, Congratulations!" << endl;
	getchar();
	finished = true;
}

void Dungeon::playerDied() {
	cout << player->getName() << " died..." << endl;
	cout << "player will be reset to before starting the dungeon" << endl;
	getchar();
	finished = true;
}

void Dungeon::fillEncounterableItems() {
	encounterableItems.push_back(new SmallPotion(1));
	encounterableItems.push_back(new MediumPotion(1));
	encounterableItems.push_back(new LargePotion(1));
	encounterableItems.push_back(new AttackUp(1));
	encounterableItems.push_back(new DefenseUp(1));
	for each (Item* i in encounterableItems)
	{
		i->setName();
	}
}

