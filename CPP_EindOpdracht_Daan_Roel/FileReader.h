#pragma once
#include <iostream>
#include <string>
#include <regex>

using namespace std;

class FileReader
{
public:
	FileReader();
	~FileReader();

	// read enemy stats
	std::string getName(const string& str);
	int getHitpoints(const string& str);
	int getLevel(const string& str);
	int getMinDamage(const string& str);
	int getMaxDamage(const string& str);
	int getHitRate(const string& str);
	int getHitChance(const string& str);
	int getBlockChance(const string& str);

	// read player stats
	std::string getPlayerName(const string& str);
	int getPlayerLevel(const string& str);
	int getPlayerExperience(const string& str);
	int getPlayerDamage(const string& str);
	int getPlayerDefense(const string& str);
	int getPlayerMaxHealth(const string& str);
	int getPlayerCurrentHealth(const string& str);
private:
};

