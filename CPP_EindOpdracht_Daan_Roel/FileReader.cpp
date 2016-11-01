#include "stdafx.h"
#include "FileReader.h"

FileReader::FileReader()
{
}

FileReader::~FileReader()
{
}

string FileReader::GetName(const string& str)
{
	string returnValue;
	regex rgx("\[(\w+);");
	smatch match;

	if (regex_search(str.begin(), str.end(), match, rgx)) {
		returnValue = match[1];
	}

	return returnValue;
}

int FileReader::GetHitpoints(const string& str)
{
	int returnValue = 0;
	regex rgx("\[\w+;\w+;\d+x\d+;\d+-\d+;\d+;(\d+)]");
	smatch match;

	if (regex_search(str.begin(), str.end(), match, rgx)) {
		string s = match[1];
		returnValue = stoi(s);
	}

	return returnValue;
}

int FileReader::GetLevel(const string& str)
{
	int returnValue = 0;
	regex rgx("\[\w+;(\w+);");
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

int FileReader::GetMinDamage(const string& str)
{
	int returnValue = 0;
	regex rgx("\[\w+;\w+;\d+x\d+;(\d+)-");
	smatch match;

	if (regex_search(str.begin(), str.end(), match, rgx)) {
		string s = match[1];
		returnValue = stoi(s);
	}

	return returnValue;
}

int FileReader::GetMaxDamage(const string& str)
{
	int returnValue = 0;
	regex rgx("\[\w+;\w+;\d+x\d+;\d+-(\d+)");
	smatch match;

	if (regex_search(str.begin(), str.end(), match, rgx)) {
		string s = match[1];
		returnValue = stoi(s);
	}

	return returnValue;
}

int FileReader::GetHitRate(const string& str)
{
	int returnValue = 0;
	regex rgx("\[\w+;\w+;\d+x(\d+);");
	smatch match;

	if (regex_search(str.begin(), str.end(), match, rgx)) {
		string s = match[1];
		returnValue = stoi(s);
	}

	return returnValue;
}

int FileReader::GetHitChance(const string& str)
{
	int returnValue = 0;
	regex rgx("\[\w+;\w+;(\d+)x");
	smatch match;

	if (regex_search(str.begin(), str.end(), match, rgx)) {
		string s = match[1];
		returnValue = stoi(s);
	}

	return returnValue;
}

int FileReader::GetBlockChance(const string& str)
{
	int returnValue = 0;
	regex rgx("\[\w+;\w+;\d+x\d+;\d+-\d+;(\d+);");
	smatch match;

	if (regex_search(str.begin(), str.end(), match, rgx)) {
		string s = match[1];
		returnValue = stoi(s);
	}

	return returnValue;
}
