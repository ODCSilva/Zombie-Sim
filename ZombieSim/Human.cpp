#include "Human.h"
#include "Config.h"
#include "City.h"
#include <vector>
#include <utility>
using namespace std;

/**
 * Default constructor.
 */
Human::Human() {
	this->type = HUMAN;
}

/**
 * Overriden constructor.
 * @param City pointer to the city the organism is in.
 * @param x Organism's x coordinates.
 * @param y Oragnism's y coordinates.
 */
Human::Human(City* city, int x, int y) {
	this->recruitCounter = 0;
	this->type = HUMAN;
	this->x = x;
	this->y = y;
	this->city = city;
}

/**
 * Virtual destructor
 */
Human::~Human() {}

/**
 * Get type for this organism. (In this case, HUMAN)
 * @return int Representing HUMAN type.
 */
int Human::getType() {
	return type;
}

/**
 * Human move routine.
 */
void Human::move() {
	if (!moved) {
		moveRandomly();

		moved = true;
	}
}

/**
 * Check if it's possible to recuit a fellow human.
 */
void Human::act() {
	if (recruitCounter >= HUMAN_RECRUIT_TURNS) {
		recruit();
	    recruitCounter = 0;
	}
	else {
		recruitCounter++;
	}
}

/**
 * Recruits a fellow human and spawns it on an unoccupied adjacent tile.
 */
void Human::recruit() {
	vector<pair<int, int>> moveOptions;

	int old_x = x;
	int old_y = y;

	if ((y - 1) >= 0) {
		if (city->getAt(x, y - 1) == nullptr) {
			pair<int, int> t(x, y - 1);
			moveOptions.push_back(t);
		}
	}

	if ((x + 1) < CITY_WIDTH) {
		if (city->getAt(x + 1, y) == nullptr) {
			pair<int, int> t(x + 1, y);
			moveOptions.push_back(t);
		}
	}

	if ((y + 1) < CITY_HEIGHT) {
		if (city->getAt(x, y + 1) == nullptr) {
			pair<int, int> t(x, y + 1);
			moveOptions.push_back(t);
		}
	}

	if ((x - 1) >= 0) {
		if (city->getAt(x - 1, y) == nullptr) {
			pair<int, int> t(x - 1, y);
			moveOptions.push_back(t);
		}
	}

	if (moveOptions.size() > 0) {
		int dir = rand() % moveOptions.size();
		int spawn_x = moveOptions[dir].first;
		int spawn_y = moveOptions[dir].second;

		Human* h = new Human(city, spawn_x, spawn_y);
		city->putAt(spawn_x, spawn_y, h);
	}
}

/**
 * Helper method to help with output using polymorphism.
 * @return output stream
 */
wostream& Human::print(wostream& out) const {

	Config::setColor(HUMAN_COLOR);
	out << HUMAN_CHAR;
	Config::setColor(8);

	return out;
}

/**
 * Overriden << operator.
 * @return output stream.
 */
wostream& operator<<(wostream &out, const Human &human) {
	return human.print(out);
}

/**
 * Chooses an unoccupied tile to move into randomly.
 */
void Human::moveRandomly() {

	vector<pair<int, int>> moveOptions;

	int old_x = x;
	int old_y = y;

	if ((y - 1) >= 0) {
		if (city->getAt(x, y - 1) == nullptr) {
			pair<int, int> t(x, y - 1);
			moveOptions.push_back(t);
		}
	}

	if ((x + 1) < CITY_WIDTH) {
		if (city->getAt(x + 1, y) == nullptr) {
			pair<int, int> t(x + 1, y);
			moveOptions.push_back(t);
		}
	}

	if ((y + 1) < CITY_HEIGHT) {
		if (city->getAt(x, y + 1) == nullptr) {
			pair<int, int> t(x, y + 1);
			moveOptions.push_back(t);
		}
	}

	if ((x - 1) >= 0) {
		if (city->getAt(x - 1, y) == nullptr) {
			pair<int, int> t(x - 1, y);
			moveOptions.push_back(t);
		}
	}

	if (moveOptions.size() > 0) {
		int dir = rand() % moveOptions.size();
		x = moveOptions[dir].first;
		y = moveOptions[dir].second;
		city->putAt(x, y, this);
		city->clearAt(old_x, old_y);
	}
}