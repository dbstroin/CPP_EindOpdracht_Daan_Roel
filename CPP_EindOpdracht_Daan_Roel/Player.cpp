#include "stdafx.h"
#include "Player.h"
#include <string>
#include "FileReader.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::savePlayer()
{
	ofstream file;
	ifstream deleteLineFile;
	deleteLineFile.open("characters.txt");
	file.open("temp.txt", std::ofstream::app);

	std::string line;
	while (getline(deleteLineFile, line)) {
		if (line.find(name) != string::npos) {
			line.replace(line.find(line), line.length(), "");
		}
		file << line << endl;
	}

	std::string characterSave = "[";

	characterSave += name + ";";
	characterSave += std::to_string(level) + ";";
	characterSave += std::to_string(experience) + ";";
	characterSave += std::to_string(damage) + ";";
	characterSave += std::to_string(defense) + ";";
	characterSave += std::to_string(maxHealth) + ";";
	characterSave += std::to_string(currHealth) + "]\n";

	file << characterSave;
	deleteLineFile.close();
	file.close();
	remove("characters.txt");
	rename("temp.txt", "characters.txt");
}

void Player::loadPlayer(std::string playerName) {
	fstream file;
	std::string path = "characters.txt";
	FileReader reader;
	file.open(path);

	std::string line;
	while (getline(file, line)) {
		if (line.find(playerName) != string::npos) {
			name = reader.getPlayerName(line);
			level = reader.getPlayerLevel(line);
			experience = reader.getPlayerExperience(line);
			damage = reader.getPlayerDamage(line);
			defense = reader.getPlayerDefense(line);
			maxHealth = reader.getPlayerMaxHealth(line);
			currHealth = reader.getPlayerCurrentHealth(line);
		}
	}
	cout << "Loaded hero!" << endl;
	cout << "Welcome, " << name << "!\n";
	cout << endl;
}

void Player::newPlayer() {
	string n;

	cout << "Please enter the heroes name" << endl;
	while (n == "") getline(cin, n);

	name = n;
	level = 1;
	experience = 0;
	damage = 10;
	defense = 10;
	maxHealth = 1000;
	currHealth = 100;
	cout << "Your new hero has been created!" << endl;
	cout << "Welcome, " << n << "!\n";
	cout << endl;
}

void Player::getHit(int damage) {

	int random = getRandom(0, 100);

	if (random > defense / 2) {
		currHealth = currHealth - damage;
		cout << "You got hit for " << damage << " damage!" << endl;
		cout << "Current Health: " << currHealth << "/" << maxHealth << endl;
	}
	else {
		cout << "You blocked the enemies attack!" << endl;
	}
}

void Player::addItem(Item * i) {
	items.push_back(i);
}

void Player::addExperience(int amount) {
	int expToNextlvl = 10;
	experience = experience + amount;
	cout << "Experience gained: " << amount << endl;
	if (experience > expToNextlvl) {
		experience = experience - expToNextlvl;
		level++;
		cout << "You leveled up! You are now level " << level << endl;
	}
	cout << "Current experience: " << experience << "/" << expToNextlvl << endl;
}

void Player::addHealth(int amount) {
	currHealth = currHealth + amount;
	if (currHealth > maxHealth) currHealth = maxHealth;
	cout << "You have been healed for " << amount << endl;
	cout << "Current Health: " << currHealth << "/" << maxHealth << endl;
}

void Player::deleteItem(Item* i) {
	items.erase(std::remove(items.begin(), items.end(), i), items.end());
}

vector<Item*> Player::getItems() {
	return items;
}

void Player::setX(int ix) {
	x = ix;
}

void Player::setY(int iy) {
	y = iy;
}

int Player::getY() {
	return y;
}

int Player::getX() {
	return x;
}

int Player::getDamage() {
	return damage;
}