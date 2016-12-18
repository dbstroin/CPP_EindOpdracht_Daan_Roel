#include "stdafx.h"
#include "Floor.h"

Floor::Floor()
{

}

Floor::~Floor()
{
}

Floor::Floor(int l, int w, int lev, Player* p)
{
	player = p;
	length = l;
	width = w;
	level = lev;
	started = false;

	createRooms();
	createEdges();
	createPossibleEnemies();	

}

void Floor::createEdges()
{
	//Connect rooms on ALL sides
	for (int wIndex = 0; wIndex < width; wIndex++)
	{
		for (int lIndex = 0; lIndex < length; lIndex++) {
			//East
			if (wIndex + 1 < width) {

				rooms[wIndex][lIndex]->setEast(rooms[wIndex + 1][lIndex]);
			}
			//West
			if (wIndex - 1 > -1) {
	
				rooms[wIndex][lIndex]->setWest(rooms[wIndex - 1][lIndex]);
			}
			//North
			if (lIndex - 1 > -1) {

				rooms[wIndex][lIndex]->setNorth(rooms[wIndex][lIndex - 1]);
			}
			//South
			if (lIndex + 1 < length) {

				rooms[wIndex][lIndex]->setSouth(rooms[wIndex][lIndex + 1]);
			}
		}
	}
}

void Floor::createRooms()
{
	rooms.reserve(width);
	//Fill grid with rooms
	for (int wIndex = 0; wIndex < width; wIndex++)
	{
		vector<Room*> temp;
		temp.reserve(length);
		for (int lIndex = 0; lIndex < length; lIndex++) {
			Room* r = new Room(wIndex, lIndex, "N");
			temp.push_back(r);
		}

		rooms.push_back(temp);
	}
}

void Floor::setStairsToNextFloor(int playerx, int playery) {
	bool randomSet = false;
	int randomx;
	int randomy;

	while (!randomSet) {
		randomx = getRandom(0, width-1);
		randomy = getRandom(0, length - 1);

		if (randomx == playerx && randomy == playery);
		else {
			randomSet = true;
		}
	}

	rooms[randomx][randomy]->setType("H");

}

void Floor::drawMap()
{
	for (int lIndex = 0; lIndex < length; lIndex++) {
		cout << "   ";

		for (int wIndex = 0; wIndex < width; wIndex++) {
			if (rooms[wIndex][lIndex]->getNorth() != nullptr) {
				cout << "| ";
			}
		}

		cout << endl;
		cout << "   ";

		for (int wIndex = 0; wIndex < width; wIndex++) {
			rooms[wIndex][lIndex]->Draw();
			if (rooms[wIndex][lIndex]->getEast() != nullptr) {
				cout << "-";
			}
		}
		cout << endl;
	}
	cout << endl;
}

void Floor::startFloor(int startx, int starty)
{
	player->setX(startx);
	player->setY(starty);
	rooms[startx][starty]->playerVisits();
	if (!started) {
		setStairsToNextFloor(startx, starty);
		started = true;
	}
}

void Floor::setStairsToPrevFloor(int x, int y) {
	rooms[x][y]->setType("D");
}

vector<string> Floor::getDirectionOptions()
{
	return rooms[player->getX()][player->getY()]->getAvailableDirections();
}

Enemy* Floor::tryEncounterEnemy() {
	int encounterChance = possibleEnemies.size() * 2;
	//int encounterChance = possibleEnemies.size() - 1; //turn on to always encounter enemy

	int randomEnemy = getRandom(0, encounterChance );

	if (randomEnemy > possibleEnemies.size() - 1 || possibleEnemies.size() < 1) {
		return NULL;
	}
	else {
		return possibleEnemies[randomEnemy];
	}
}

void Floor::deleteEnemy(Enemy* enemy) {
	possibleEnemies.erase(std::remove(possibleEnemies.begin(), possibleEnemies.end(), enemy), possibleEnemies.end());
}

bool Floor::getIfOnPlayerOnStairs() {
	if (rooms[player->getX()][player->getY()]->getType() == "H") return true;
	else return false;
}

void Floor::movePlayer(int direction, vector<string> options) 
{
	rooms[player->getX()][player->getY()]->playerLeaves();
	if (options[direction] == "north") {
		rooms[player->getX()][player->getY()]->getNorth()->playerVisits();
		player->setY(player->getY() - 1);
	}
	if (options[direction] == "east") {
		rooms[player->getX()][player->getY()]->getEast()->playerVisits();
		player->setX(player->getX() + 1);
	}
	if (options[direction] == "south") {
		rooms[player->getX()][player->getY()]->getSouth()->playerVisits();
		player->setY(player->getY() + 1);
	}
	if (options[direction] == "west") {
		rooms[player->getX()][player->getY()]->getWest()->playerVisits();
		player->setX(player->getX() - 1);
	}
}

void Floor::createPossibleEnemies()
{
	fstream file;
	FileReader reader;
	file.open("monsters.txt");

	string line;
	while (getline(file, line)) {
		if (line.substr(0,1) == "[") {
			Enemy* newEnemy = new Enemy();

			newEnemy->name = reader.getName(line);
			newEnemy->level = reader.getLevel(line);
			newEnemy->hitPoints = reader.getHitpoints(line);
			newEnemy->hitAmount = reader.getHitRate(line);
			newEnemy->hitChance = reader.getHitChance(line);
			newEnemy->minDamage = reader.getMinDamage(line);
			newEnemy->maxDamage = reader.getMaxDamage(line);
			newEnemy->blockChance = reader.getBlockChance(line);

			if (newEnemy->level < 0 && (level + 1) >= 5) {
				possibleEnemies.push_back(newEnemy);
			}
			else if (newEnemy->level <= level + 1 && newEnemy->level > 0) {
				possibleEnemies.push_back(newEnemy);
			}
			else {
				delete newEnemy;
			}
		}
	}

}

void Floor::useTalisman() {
		int a = breadthFirstSearch(rooms[player->getX()][player->getY()]);
		cout << "De talisman zegt dat de trap " << a << " kamers ver weg is." << endl;
}

void Floor::depthFirstSearch(Room* startRoom) {

}

void Floor::depthFirstSearch(Room * vertex, vector<Room*> visited)
{
}

int Floor::breadthFirstSearch(Room* startRoom) {
	vector<Room*> queue;
	vector<Room*> visited;

	queue.push_back(startRoom);
	int staircaseAway = 0;

	while (queue.size() > 0) {
		Room* vertex = queue[0];
		visited.push_back(vertex);
		queue.erase(std::remove(queue.begin(), queue.end(), vertex), queue.end());

		for each (Room* adjacentRoom in vertex->getAdjacentRooms())
		{
			if (adjacentRoom->getType() == "H") {
				staircaseAway++;
				return staircaseAway;
			}
			else {
				if (find(visited.begin(), visited.end(), adjacentRoom) == visited.end()) {
					if (find(visited.begin(), visited.end(), adjacentRoom) == visited.end()) {
						queue.push_back(adjacentRoom);
					}
				}
			}
		}
		staircaseAway++;
	}
}

void Floor::clear() {
	for (int wIndex = 0; wIndex < width; wIndex++)
	{
		for (int lIndex = 0; lIndex < length; lIndex++) {
			delete rooms[wIndex][lIndex];
		}
	}
	for each (Enemy* enemy in possibleEnemies)
	{
		delete enemy;
	}
}

