#include "stdafx.h"
#include "FileReader.h"

FileReader::FileReader()
{
}

FileReader::~FileReader()
{
}

string FileReader::getName(const string& str)
{
	string returnValue;
	regex rgx("\\[(\\w+\\s*\\w*);");
	smatch match;

	if (regex_search(str.begin(), str.end(), match, rgx)) {
		returnValue = match[1];
	}

	return returnValue;
}

int FileReader::getHitpoints(const string& str)
{
	int returnValue = 0;
	regex rgx("\\[\\w+\\s*\\w*;\\w+;\\d+x\\d+;\\d+-\\d+;\\d+;(\\d+)");
	smatch match;

	if (regex_search(str.begin(), str.end(), match, rgx)) {
		string s = match[1];
		returnValue = stoi(s);
	}

	return returnValue;
}

int FileReader::getLevel(const string& str)
{
	int returnValue = 0;
	regex rgx("\\[\\w+\\s*\\w*;(\\w+);");
	smatch match;

	if (regex_search(str.begin(), str.end(), match, rgx)) {
		string s = match[1];
		if (s == "BAAS") {
			returnValue = -1;		// -1 betekend dat die enemy een baas is.
		}
		else
		{
			returnValue = stoi(s);
		}
	}

	return returnValue;
}

int FileReader::getMinDamage(const string& str)
{
	int returnValue = 0;
	regex rgx("\\[\\w+\\s*\\w*;\\w+;\\d+x\\d+;(\\d+)-");
	smatch match;

	if (regex_search(str.begin(), str.end(), match, rgx)) {
		string s = match[1];
		returnValue = stoi(s);
	}

	return returnValue;
}

int FileReader::getMaxDamage(const string& str)
{
	int returnValue = 0;
	regex rgx("\\[\\w+\\s*\\w*;\\w+;\\d+x\\d+;\\d+-(\\d+)");
	smatch match;

	if (regex_search(str.begin(), str.end(), match, rgx)) {
		string s = match[1];
		returnValue = stoi(s);
	}

	return returnValue;
}

int FileReader::getHitRate(const string& str)
{
	int returnValue = 0;
	regex rgx("\\[\\w+\\s*\\w*;\\w+;\\d+x(\\d+);");
	smatch match;

	if (regex_search(str.begin(), str.end(), match, rgx)) {
		string s = match[1];
		returnValue = stoi(s);
	}

	return returnValue;
}

int FileReader::getHitChance(const string& str)
{
	int returnValue = 0;
	regex rgx("\\[\\w+\\s*\\w*;\\w+;(\\d+)x");
	smatch match;

	if (regex_search(str.begin(), str.end(), match, rgx)) {
		string s = match[1];
		returnValue = stoi(s);
	}

	return returnValue;
}

int FileReader::getBlockChance(const string& str)
{
	int returnValue = 0;
	regex rgx("\\[\\w+\\s*\\w*;\\w+;\\d+x\\d+;\\d+-\\d+;(\\d+);");
	smatch match;

	if (regex_search(str.begin(), str.end(), match, rgx)) {
		string s = match[1];
		returnValue = stoi(s);
	}

	return returnValue;
}

std::string FileReader::getPlayerName(const string & str)
{
	string returnValue;

	regex rgx("\\[(\\w+\\s*\\w*);");
	smatch match;

	if (regex_search(str.begin(), str.end(), match, rgx)) {
		returnValue = match[1];
	}

	return returnValue;
}

int FileReader::getPlayerLevel(const string & str)
{
	int returnValue = 0;
	regex rgx("\\[\\w+\\s*\\w*;(\\d+)");
	smatch match;

	if (regex_search(str.begin(), str.end(), match, rgx)) {
		string s = match[1];
		returnValue = stoi(s);
	}
	return returnValue;
}

int FileReader::getPlayerExperience(const string & str)
{
	int returnValue = 0;
	regex rgx("\\[\\w+\\s*\\w*;\\d+;(\\d+)");
	smatch match;

	if (regex_search(str.begin(), str.end(), match, rgx)) {
		string s = match[1];
		returnValue = stoi(s);
	}
	return returnValue;
}

int FileReader::getPlayerDamage(const string & str)
{
	int returnValue = 0;
	regex rgx("\\[\\w+\\s*\\w*;\\d+;\\d+;(\\d+)");
	smatch match;

	if (regex_search(str.begin(), str.end(), match, rgx)) {
		string s = match[1];
		returnValue = stoi(s);
	}
	return returnValue;
}

int FileReader::getPlayerDefense(const string & str)
{
	int returnValue = 0;
	regex rgx("\\[\\w+\\s*\\w*;\\d+;\\d+;\\d+;(\\d+)");
	smatch match;

	if (regex_search(str.begin(), str.end(), match, rgx)) {
		string s = match[1];
		returnValue = stoi(s);
	}
	return returnValue;
}

int FileReader::getPlayerMaxHealth(const string & str)
{
	int returnValue = 0;
	regex rgx("\\[\\w+\\s*\\w*;\\d+;\\d+;\\d+;\\d+;(\\d+)");
	smatch match;

	if (regex_search(str.begin(), str.end(), match, rgx)) {
		string s = match[1];
		returnValue = stoi(s);
	}
	return returnValue;
}

int FileReader::getPlayerCurrentHealth(const string & str)
{
	int returnValue = 0;
	regex rgx("\\[\\w+\\s*\\w*;\\d+;\\d+;\\d+;\\d+;\\d+;(\\d+)");
	smatch match;

	if (regex_search(str.begin(), str.end(), match, rgx)) {
		string s = match[1];
		returnValue = stoi(s);
	}
	return returnValue;
}
