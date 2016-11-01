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
	string GetName(const string& str);
	int GetHitpoints(const string& str);
	int GetLevel(const string& str);
	int GetMinDamage(const string& str);
	int GetMaxDamage(const string& str);
	int GetHitRate(const string& str);
	int GetHitChance(const string& str);
	int GetBlockChance(const string& str);
private:
};

