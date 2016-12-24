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

	createRooms();
	createEdges();
	//randomizeFloor();
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

void Floor::randomizeFloor() {
	int removeEdges = width * length / 2;
	for (int i = 0; i < removeEdges; i++) {
		int randomX = getRandom(0, width-1);
		int randomY = getRandom(0, length-1);

		int randomSide = getRandom(0, 3);
		if (randomSide == 0) { //North
			if (rooms[randomX][randomY]->getNorth() != nullptr) {
				rooms[randomX][randomY]->setNorth(nullptr);
				rooms[randomX][randomY - 1]->setSouth(nullptr);
			}
		}
		if (randomSide == 1) { //East
			if (rooms[randomX][randomY]->getEast() != nullptr) {
				rooms[randomX][randomY]->setEast(nullptr);
				rooms[randomX + 1][randomY]->setWest(nullptr);
			}
		}
		if (randomSide == 2) { //West
			if (rooms[randomX][randomY]->getWest() != nullptr) {
				rooms[randomX][randomY]->setWest(nullptr);
				rooms[randomX - 1][randomY]->setEast(nullptr);
			}
		}
		if (randomSide == 3) { //South
			if (rooms[randomX][randomY]->getSouth() != nullptr) {
				rooms[randomX][randomY]->setSouth(nullptr);
				rooms[randomX][randomY + 1]->setNorth(nullptr);
			}
		}
	}
}

void Floor::drawMap()
{
	for (int lIndex = 0; lIndex < length; lIndex++) {
		std::cout << "   ";

		for (int wIndex = 0; wIndex < width; wIndex++) {
			if (rooms[wIndex][lIndex]->getNorth() != nullptr) {
				std::cout << "| ";
			}
			else std::cout << "  ";
		}

		std::cout << endl;
		std::cout << "   ";

		for (int wIndex = 0; wIndex < width; wIndex++) {
			rooms[wIndex][lIndex]->Draw();
			if (rooms[wIndex][lIndex]->getEast() != nullptr) {
				std::cout << "-";
			}
			else std::cout << " ";
		}
		std::cout << endl;
	}
	std::cout << endl;
}

void Floor::setStairsToPrevFloor(int x, int y) {
	rooms[x][y]->setType("D");
}

std::pair<int, int> Floor::setStairsToNextFloor(int xNot, int yNot) {
	bool randomSet = false;
	int randomx;
	int randomy;

	while (!randomSet) {
		randomx = getRandom(0, width - 1);
		randomy = getRandom(0, length - 1);

		if (randomx != xNot || randomy != yNot)	randomSet = true;
		
	}

	rooms[randomx][randomy]->setType("H");
	std::pair<int, int> pair(randomx, randomy);
	return pair;
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
	vector<Enemy> bosses;

	string line;
	while (getline(file, line)) {
		if (line.substr(0,1) == "[") {
			if (reader.getLevel(line) < 0) {
				Enemy newBoss;

				newBoss.name = reader.getName(line);
				newBoss.level = reader.getLevel(line);
				newBoss.hitPoints = reader.getHitpoints(line);
				newBoss.hitAmount = reader.getHitRate(line);
				newBoss.hitChance = reader.getHitChance(line);
				newBoss.minDamage = reader.getMinDamage(line);
				newBoss.maxDamage = reader.getMaxDamage(line);
				newBoss.blockChance = reader.getBlockChance(line);

				bosses.push_back(newBoss);
			}
			else if (reader.getLevel(line) <= level + 1 && reader.getLevel(line) > 0) {
				Enemy* newEnemy = new Enemy();

				newEnemy->name = reader.getName(line);
				newEnemy->level = reader.getLevel(line);
				newEnemy->hitPoints = reader.getHitpoints(line);
				newEnemy->hitAmount = reader.getHitRate(line);
				newEnemy->hitChance = reader.getHitChance(line);
				newEnemy->minDamage = reader.getMinDamage(line);
				newEnemy->maxDamage = reader.getMaxDamage(line);
				newEnemy->blockChance = reader.getBlockChance(line);

				possibleEnemies.push_back(newEnemy);
			}
		}
	}

	if (bosses.size() > 0) {
		int randomBoss = getRandom(0, bosses.size() - 1);
		boss = new Enemy();
		*boss = bosses[randomBoss];
	}

	file.close();
}

void Floor::setBossLocation() {
	bool randomSet = false;
	int randomx;
	int randomy;

	while (!randomSet) {
		randomx = getRandom(0, width - 1);
		randomy = getRandom(0, length - 1);

		if (randomx == player->getX() && randomy == player->getY());
		else {
			randomSet = true;
		}
	}

	rooms[randomx][randomy]->setType("B");

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
	for each (Enemy* enemy in possibleEnemies) delete enemy;
	delete boss;
}

