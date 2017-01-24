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
	//createEdges();
	createPossibleEnemies();

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
			r->setRandomBeschrijving();
			temp.push_back(r);
		}

		rooms.push_back(temp);
	}
}

void Floor::randomizeFloor() {
	int stairsUpX = 0;
	int stairsUpY = 0;
	int stairsDownX = player->getX();
	int stairsDownY = player->getY();

	for (int x = 0; x < width; x++) {
		for (int y = 0; y < length; y++) {
			if (rooms[x][y]->getType() == "H" || rooms[x][y]->getType() == "B") {
				stairsUpX = x;
				stairsUpY = y;
			}
			if (rooms[x][y]->getType() == "D") {
				stairsDownX = x;
				stairsDownY = y;
			}
		}
	}

	int roomX = stairsDownX;
	int roomY = stairsDownY;

	while (roomX != stairsUpX || roomY != stairsUpY) {
		int random = getRandom(0, 1);
		if (random == 0) {
			if (stairsUpX > roomX) {
				rooms[roomX][roomY]->setEast(rooms[roomX + 1][roomY]);
				rooms[roomX + 1][roomY]->setWest(rooms[roomX][roomY]);
				roomX++;
			}
			if (stairsUpX < roomX) {
				rooms[roomX][roomY]->setWest(rooms[roomX - 1][roomY]);
				rooms[roomX - 1][roomY]->setEast(rooms[roomX][roomY]);
				roomX--;
			}
		}

		if (random == 1) {
			if (stairsUpY > roomY) {
				rooms[roomX][roomY]->setSouth(rooms[roomX][roomY + 1]);
				rooms[roomX][roomY + 1]->setNorth(rooms[roomX][roomY]);
				roomY++;
			}
			if (stairsUpY < roomY) {
				rooms[roomX][roomY]->setNorth(rooms[roomX][roomY - 1]);
				rooms[roomX][roomY - 1]->setSouth(rooms[roomX][roomY]);
				roomY--;
			}
		}

		connectRandomRoom(roomX, roomY);
	}

	setEnemyLocations();
}

void Floor::addTauntEnemy(int xPos, int yPos)
{
	if (xPos >= 0 && xPos < width) {
		if (yPos >= 0 && yPos < length) {
			Enemy* newEnemy = new Enemy();

			newEnemy->name = "lopende muur";
			newEnemy->level = 0;
			newEnemy->hitChance = 100;
			newEnemy->hitAmount = 1;
			newEnemy->minDamage = 0;
			newEnemy->maxDamage = 0;
			newEnemy->blockChance = 1;
			newEnemy->hitPoints = 99;

			rooms[xPos][yPos]->setEnemy(newEnemy);
		}
	}
}

void Floor::setEdgeCosts() {
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < length; y++) {
			if (rooms[x][y]->getNorth() != nullptr) {
				int random = getRandom(1, 10);
				rooms[x][y]->northCost = random;
				rooms[x][y]->getNorth()->southCost = random;
			}
			if (rooms[x][y]->getEast() != nullptr) {
				int random = getRandom(1, 10);
				rooms[x][y]->eastCost = random;
				rooms[x][y]->getEast()->westCost = random;
			}
			if (rooms[x][y]->getSouth() != nullptr) {
				int random = getRandom(1, 10);
				rooms[x][y]->southCost = random;
				rooms[x][y]->getSouth()->northCost = random;
			}
			if (rooms[x][y]->getWest() != nullptr) {
				int random = getRandom(1, 10);
				rooms[x][y]->westCost = random;
				rooms[x][y]->getWest()->eastCost = random;
			}
		}
	}
}

void Floor::connectRandomRoom(int x, int y) {
	int randomConnects = getRandom(1, 10);

	while (randomConnects > 0) {
		int random = getRandom(0, 3);
		switch (random) {
		case(0):
			if (x < width - 1) {
				rooms[x][y]->setEast(rooms[x + 1][y]);
				rooms[x + 1][y]->setWest(rooms[x][y]);
				x++;
			}
			break;
		case(1):
			if (x > 0) {
				rooms[x][y]->setWest(rooms[x - 1][y]);
				rooms[x - 1][y]->setEast(rooms[x][y]);
				x--;
			}
			break;
		case(2):
			if (y < length - 1) {
				rooms[x][y]->setSouth(rooms[x][y + 1]);
				rooms[x][y + 1]->setNorth(rooms[x][y]);
				y++;
			}
			break;
		case(3):
			if (y > 0) {
				rooms[x][y]->setNorth(rooms[x][y - 1]);
				rooms[x][y - 1]->setSouth(rooms[x][y]);
				y--;
			}
			break;
		}
		randomConnects--;
	}
}

void Floor::drawMap()
{
	for (int lIndex = 0; lIndex < length; lIndex++) {
		std::cout << "   ";

		for (int wIndex = 0; wIndex < width; wIndex++) {
			if (rooms[wIndex][lIndex]->getNorth() != nullptr) {
				if (rooms[wIndex][lIndex]->getNorth()->getVisited() || rooms[wIndex][lIndex]->getVisited() || showAllRooms) {
					if(rooms[wIndex][lIndex]->northIsCollapsed) std::cout << "~ ";
					else std::cout << "| ";
				}
				else std::cout << "  ";
			}
			else std::cout << "  ";
		}

		std::cout << endl;
		std::cout << "   ";

		for (int wIndex = 0; wIndex < width; wIndex++) {
			rooms[wIndex][lIndex]->Draw();
			if (rooms[wIndex][lIndex]->getEast() != nullptr) {
				if (rooms[wIndex][lIndex]->getEast()->getVisited() || rooms[wIndex][lIndex]->getVisited() || showAllRooms) {
					if (rooms[wIndex][lIndex]->eastIsCollapsed) std::cout << "~";
					else std::cout << "-";
				}
				else std::cout << " ";
			}
			else std::cout << " ";
		}
		std::cout << endl;
	}
	std::cout << endl;
}

void Floor::drawMapHitpoints()
{
	for (int lIndex = 0; lIndex < length; lIndex++) {
		std::cout << "   ";

		for (int wIndex = 0; wIndex < width; wIndex++) {
			if (rooms[wIndex][lIndex]->getNorth() != nullptr) {
				if (rooms[wIndex][lIndex]->getNorth()->getVisited() || rooms[wIndex][lIndex]->getVisited() || showAllRooms) {
					if (rooms[wIndex][lIndex]->northIsCollapsed) std::cout << "~ ";
					else std::cout << "| ";
				}
				else std::cout << "  ";
			}
			else std::cout << "  ";
		}

		std::cout << endl;
		std::cout << "   ";

		for (int wIndex = 0; wIndex < width; wIndex++) {
			rooms[wIndex][lIndex]->DrawHitpoints();
			if (rooms[wIndex][lIndex]->getEast() != nullptr) {
				if (rooms[wIndex][lIndex]->getEast()->getVisited() || rooms[wIndex][lIndex]->getVisited() || showAllRooms) {
					if (rooms[wIndex][lIndex]->eastIsCollapsed) std::cout << "~";
					else std::cout << "-";
				}
				else std::cout << " ";
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

	int randomEnemy = getRandom(0, encounterChance);

	if (randomEnemy > possibleEnemies.size() - 1 || possibleEnemies.size() < 1) {
		return NULL;
	}
	else {
		return possibleEnemies[randomEnemy];
	}
}

Enemy* Floor::getEnemy(int x, int y) {
	return rooms[x][y]->getEnemy();
}

void Floor::deleteEnemy(Enemy* enemy, int x, int y) {
	possibleEnemies.erase(std::remove(possibleEnemies.begin(), possibleEnemies.end(), enemy), possibleEnemies.end());
	delete enemy;
	rooms[x][y]->setEnemy(nullptr);

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
	try {
		file.open("monsters.txt");
	}
	catch (exception ex) {
		// Als het bestand niet kan worden gevonden kan de speler geen vijanden tegenkomen. Er kan nog wel gespeeld worden.
		std::cout << "There was an error with opening the file 'monsters.txt'. No monsters can be encountered." << std::endl;
		return;
	}
	vector<Enemy> bosses;

	string line;
	while (getline(file, line)) {
		if (line.substr(0, 1) == "[") {
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
		boss = bosses[randomBoss];
	}

	file.close();
}

void Floor::setEnemyLocations() {
	int done = 0;

	for each (Enemy* enemy in possibleEnemies)
	{
		bool set = false;
		while (!set && done < 1000) {
			done++;
			int x = getRandom(0, width - 1);
			int y = getRandom(0, length - 1);

			if (rooms[x][y]->getAvailableDirections().size() > 0) {
				if (rooms[x][y]->getEnemy() == nullptr && rooms[x][y]->getType() == "N") {
					rooms[x][y]->setEnemy(enemy);
					set = true;
				}
			}
		}
	}
}

void Floor::setBossLocation() {
	bool randomSet = false;
	int randomx;
	int randomy;

	while (!randomSet) {
		randomx = getRandom(0, width - 1);
		randomy = getRandom(0, length - 1);

		if (randomx == player->getX() && randomy == player->getY());
		else if (rooms[randomx][randomy]->getType() == "D");
		else {
			randomSet = true;
		}
	}

	rooms[randomx][randomy]->setType("B");

}

void Floor::useTalisman() {
	int a = breadthFirstSearch(rooms[player->getX()][player->getY()], 0);
	resetSearchVisitedRooms();
	cout << "De talisman zegt dat de trap " << a << " kamers ver weg is." << endl;
}

void Floor::useCompass()
{
	std::vector<std::string> path = dijkstraSearch(rooms[player->getX()][player->getY()]);
	std::cout << "het kompas brand een aantal worden op de vloer:" << std::endl;
	for each (std::string direction in path)
	{
		std::cout << " -> " << direction;
	}
	std::cout << ::endl;
}

void Floor::useGrenade()
{
	int startX = 0;
	int startY = 0;

	//Check welke rooms bereikt moeten kunnen worden en locatie van Trap/Baas opslaan in startX en startY om vanuit daar het algoritme te starten;
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < length; y++) {
			if (rooms[x][y]->getAdjacentRooms().size() > 0) {
				rooms[x][y]->shouldBeVisitable = true;
				rooms[x][y]->isVisitable = false;
				if (rooms[x][y]->getType() == "H" || rooms[x][y]->getType() == "B") {
					startX = x;
					startY = y;
				}

				if (rooms[x][y]->getNorth() != nullptr) rooms[x][y]->northIsCollapsed = true;
				if (rooms[x][y]->getEast() != nullptr) rooms[x][y]->eastIsCollapsed = true;
				if (rooms[x][y]->getWest() != nullptr) rooms[x][y]->westIsCollapsed = true;
				if (rooms[x][y]->getSouth() != nullptr) rooms[x][y]->southIsCollapsed = true;
			}
		}
	}

	primsAlgorithm(rooms[startX][startY]);

	removeTooManyCollapsedRooms();
}

void Floor::primsAlgorithm(Room* startRoom) {
	startRoom->isVisitable = true;
	bool northDone = false;
	bool southDone = false;
	bool eastDone = false;
	bool westDone = false;

	while (!northDone || !southDone || !westDone || !eastDone)
	{
		int random = getRandom(0, 3);

		switch (random) {
		case 0:
			if (startRoom->getNorth() != nullptr) {
				if (startRoom->getNorth()->isVisitable == false) {
					startRoom->northIsCollapsed = false;
					startRoom->getNorth()->southIsCollapsed = false;
					primsAlgorithm(startRoom->getNorth());
				}
			}
			northDone = true;
			break;
		case 1:
			if (startRoom->getEast() != nullptr) {
				if (startRoom->getEast()->isVisitable == false) {
					startRoom->eastIsCollapsed = false;
					startRoom->getEast()->westIsCollapsed = false;
					primsAlgorithm(startRoom->getEast());
				}
			}
			eastDone = true;
			break;
		case 2:
			if (startRoom->getSouth() != nullptr) {
				if (startRoom->getSouth()->isVisitable == false) {
					startRoom->southIsCollapsed = false;
					startRoom->getSouth()->northIsCollapsed = false;
					primsAlgorithm(startRoom->getSouth());
				}
			}
			southDone = true;
		break;
		case 3:
			if (startRoom->getWest() != nullptr) {
				if (startRoom->getWest()->isVisitable == false) {
					startRoom->westIsCollapsed = false;
					startRoom->getWest()->eastIsCollapsed = false;
					primsAlgorithm(startRoom->getWest());
				}
			}
			westDone = true;
		break;
		}
	}
}

void Floor::primsAlgorithm(Room* startRoom, direction d) {
	switch (d) {
	case NORTH:
		if (startRoom->getNorth() != nullptr) {
			if (startRoom->getNorth()->isVisitable == false) {
				startRoom->northIsCollapsed = false;
				startRoom->getNorth()->southIsCollapsed = false;
				primsAlgorithm(startRoom->getNorth());
			}
		}
		break;
	case EAST:
		if (startRoom->getEast() != nullptr) {
			if (startRoom->getEast()->isVisitable == false) {
				startRoom->eastIsCollapsed = false;
				startRoom->getEast()->westIsCollapsed = false;
				primsAlgorithm(startRoom->getEast());
			}
		}
		break;
	case SOUTH:
		if (startRoom->getSouth() != nullptr) {
			if (startRoom->getSouth()->isVisitable == false) {
				startRoom->southIsCollapsed = false;
				startRoom->getSouth()->northIsCollapsed = false;
				primsAlgorithm(startRoom->getSouth());
			}
		}
		break;
	case WEST:
		if (startRoom->getWest() != nullptr) {
			if (startRoom->getWest()->isVisitable == false) {
				startRoom->westIsCollapsed = false;
				startRoom->getWest()->eastIsCollapsed = false;
				primsAlgorithm(startRoom->getWest());
			}
		}
		break;
	}
}

void Floor::removeTooManyCollapsedRooms() {
	int maxCollapsedRooms = getRandom(10, 15);
	int collapsedRooms = 0;

	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < length; y++) {
			if (rooms[x][y]->getAdjacentRooms().size() > 0) {
				if (rooms[x][y]->eastIsCollapsed) {
					collapsedRooms++;
				}
				if (rooms[x][y]->northIsCollapsed) {
					collapsedRooms++;
				}
			}
		}
	}

	while (collapsedRooms > maxCollapsedRooms) {
		int randomX = getRandom(0, width - 1);
		int randomY = getRandom(0, length - 1);
		if (rooms[randomX][randomY]->northIsCollapsed) {
			rooms[randomX][randomY]->northIsCollapsed = false;
			collapsedRooms--;
		}
		if (rooms[randomX][randomY]->southIsCollapsed) {
			rooms[randomX][randomY]->southIsCollapsed = false;
			collapsedRooms--;
		}
		if (rooms[randomX][randomY]->eastIsCollapsed) {
			rooms[randomX][randomY]->eastIsCollapsed = false;
			collapsedRooms--;
		}
		if (rooms[randomX][randomY]->westIsCollapsed) {
			rooms[randomX][randomY]->westIsCollapsed = false;
			collapsedRooms--;
		}
	}
}

void Floor::resetSearchVisitedRooms() {
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < length; y++) {
			rooms[x][y]->setSearchVisited(false);
		}
	}
}

void Floor::depthFirstSearch(Room* startRoom) {

}

void Floor::depthFirstSearch(Room * vertex, vector<Room*> visited)
{
}

int Floor::breadthFirstSearch(Room* startRoom, int currentDistance) {
	int counter = 0;

	std::queue<Room *> frontier;
	frontier.push(startRoom);

	std::unordered_map<Room *, Room*> came_from;
	came_from[startRoom] = startRoom;

	while (!frontier.empty()) {
		Room* current = frontier.front();
		frontier.pop();

		for (auto next : current->getAdjacentRooms()) {
			if (!came_from.count(next)) {
				came_from[next] = current;
				frontier.push(next);
			}
		}
	}

	Room* currentRoom = startRoom;
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < length; y++) {
			if (rooms[x][y]->getType() == "H" || rooms[x][y]->getType() == "B") {
				currentRoom = rooms[x][y];
			}
		}
	}

	while (true) {
		if (startRoom == currentRoom) {
			break;
		}
		else {
			currentRoom = came_from[currentRoom];
			counter++;
		}
	}
	return counter;
}

std::vector<std::string> Floor::dijkstraSearch(Room * startRoom)
{
	std::priority_queue<Room*> frontier;
	frontier.push(startRoom);

	std::unordered_map<Room *, Room*> came_from;
	std::unordered_map<Room *, double> cost_so_far;
	came_from[startRoom] = startRoom;
	cost_so_far[startRoom] = 0;

	while (!frontier.empty()) {
		auto current = frontier.top();
		frontier.pop();

		for (auto next : current->getAdjacentRooms()) {
			double new_cost = cost_so_far[current] + next->GetCombinedHitPoints();
			if (!came_from.count(next) || new_cost < cost_so_far[next]) {
				cost_so_far[next] = new_cost;
				came_from[next] = current;
				frontier.push(next);
			}
		}
	}

	std::vector<Room *> path;
	Room* goal = startRoom;
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < length; y++) {
			if (rooms[x][y]->getType() == "H" || rooms[x][y]->getType() == "B") {
				goal = rooms[x][y];
			}
		}
	}
	Room* currentRoom = goal;
	path.push_back(goal);
	while (currentRoom != startRoom) {
		currentRoom = came_from[currentRoom];
		path.push_back(currentRoom);
	}
	std::reverse(path.begin(), path.end()); // pad wordt vanaf doel naar start gemaakt, omdraairen om van start naar doel te gaan

	std::vector<std::string> directions;
	for (int x = 0; x < path.size() - 1; x++) {
		Room* c = path[x];
		if (c->getEast() != nullptr && c->getEast() == path[x + 1]) {
			directions.push_back("East");
		}
		else if (c->getWest() != nullptr && c->getWest() == path[x + 1]) {
			directions.push_back("West");
		}
		else if(c->getNorth() != nullptr && c->getNorth() == path[x + 1]) {
			directions.push_back("North");
		}
		else if (c->getSouth() != nullptr && c->getSouth() == path[x + 1]) {
			directions.push_back("South");
		}
	}
	return directions;
}

void Floor::clear() {
	for (int wIndex = 0; wIndex < width; wIndex++)
	{
		for (int lIndex = 0; lIndex < length; lIndex++) {
			delete rooms[wIndex][lIndex];
		}
	}
	for each (Enemy* enemy in possibleEnemies) delete enemy;
	//	delete boss;
}

