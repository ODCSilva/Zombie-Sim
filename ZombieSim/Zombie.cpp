#include "Zombie.h"
#include "Config.h"
#include "City.h"
#include <vector>
#include <utility>
using namespace std;

/**
 * Default constructor.
 */
Zombie::Zombie(void) {
	this->type = ZOMBIE;
}

/**
 * Overriden constructor
 * @param City pointer to the city the organism is in
 * @param x Organism's x coordinates
 * @param y Oragnism's y coordinates
 */
Zombie::Zombie(City* city, int x, int y) {
	this->convertCounter = 0;
	this->starveCounter = 0;
	this->type = ZOMBIE;
	this->x = x;
	this->y = y;
	this->city = city;
}

/**
 * Virtual destructor
 */
Zombie::~Zombie() {}

/**
 * Get type for this organism. (In this case, ZOMBIE)
 * @return int Representing ZOMBIE type.
 */
int Zombie::getType() {
	return type;
}

/**
 * Zombie's move routine.
 */
void Zombie::move() {
	
	// Check for human on adjacent tiles, if there is any, eat them,
	// otherwise move to a random tile.


	// Check surrounding tiles for eating/moving opportunities
	Organism* victim;
	victim = findVictim();

	if (!moved) {
		if (victim != nullptr) {
			eatVictim(victim);
			starveCounter = 0;
		}
		else if (!moved) {
			moveRandomly();
			starveCounter++;
		}
		moved = true;
	}
}

/**
 * Check for victims to convert, and check if zombie is dying of starvation.
 */
void Zombie::act() {
	if (convertCounter >= ZOMBIE_CONVERT_TURNS) {
		Organism* victim = findVictim();

		if (victim != nullptr) {
			convertVictim(victim);
			convertCounter = 0;
		}
		else {
			convertCounter++;
		}
	}
	else {
		convertCounter++;
	}

	// Starvation check
	if (starveCounter >= ZOMBIE_STARVE_TURNS) {
		transform();
	}
}

/**
 * Transform into a human if zombie has starved.
 */
void Zombie::transform() {
	Human* h = new Human(city, x, y);
	city->putAt(x, y, h);

	delete this;
}

/**
 * Convert victim to zombie.
 * @param The victim to convert.
 */
void Zombie::convertVictim(Organism* victim) {
	int v_x = victim->getX();
	int v_y = victim->getY();

	Zombie* z = new Zombie(city, v_x, v_y);
	city->putAt(v_x, v_y, z);

	delete victim;
}

/**
 * Helper method to help with output using polymorphism.
 * @return output stream
 */
wostream& Zombie::print(wostream& out) const {

	Config::setColor(ZOMBIE_COLOR);
	out << ZOMBIE_CHAR;
	Config::setColor(8);

	return out;
}

/**
 * Overriden << operator.
 * @return output stream.
 */
wostream& operator<<(wostream &out, const Zombie &zombie) {
	return zombie.print(out);
}

/**
 * Chooses an unoccupied tile to move into randomly. 
 */
void Zombie::moveRandomly() {

	vector<pair<int, int>> moveOptions;

	int old_x = x;
	int old_y = y;

	if ((y - 1) >= 0) {
		if (city->getAt(x, y - 1) == nullptr) {
			pair<int, int> t(x, y - 1);
			moveOptions.push_back(t);
		}
	}

	if ((y - 1) >= 0 && (x + 1) < CITY_WIDTH) {
		if (city->getAt(x + 1, y - 1) == nullptr) {
			pair<int, int> t(x + 1, y - 1);
			moveOptions.push_back(t);
		}
	}

	if ((x + 1) < CITY_WIDTH) {
		if (city->getAt(x + 1, y) == nullptr) {
			pair<int, int> t(x + 1, y);
			moveOptions.push_back(t);
		}
	}

	if ((x + 1) < CITY_WIDTH && (y + 1) < CITY_HEIGHT) {
		if (city->getAt(x + 1, y + 1) == nullptr) {
			pair<int, int> t(x + 1, y + 1);
			moveOptions.push_back(t);
		}
	}

	if ((y + 1) < CITY_HEIGHT) {
		if (city->getAt(x, y + 1) == nullptr) {
			pair<int, int> t(x, y + 1);
			moveOptions.push_back(t);
		}
	}

	if ((x - 1) >= 0 && (y + 1) < CITY_HEIGHT) {
		if (city->getAt(x - 1, y + 1) == nullptr) {
			pair<int, int> t(x - 1, y + 1);
			moveOptions.push_back(t);
		}
	}

	if ((x - 1) >= 0) {
		if (city->getAt(x - 1, y) == nullptr) {
			pair<int, int> t(x - 1, y);
			moveOptions.push_back(t);
		}
	}

	if ((x - 1) >= 0 && (y - 1) >= 0) {
		if (city->getAt(x - 1, y - 1) == nullptr) {
			pair<int, int> t(x - 1, y - 1);
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

/**
 * Check adjacent tiles for a potential victim.
 * @return The organism (victim) pointer.
 */
Organism* Zombie::findVictim() {

	vector<Organism*> victims;

	//North
	if ((y - 1) >= 0) {
		Organism* o = city->getAt(x, y - 1);
		if (o != nullptr && o->getType() == HUMAN) {
			victims.push_back(o);
		}
	}

	//North East
	if ((y - 1) >= 0 && (x + 1) < CITY_WIDTH) {
		Organism* o = city->getAt(x + 1, y - 1);
		if (o != nullptr && o->getType() == HUMAN) {
			victims.push_back(o);
		}
	}

	//East
	if ((x + 1) < CITY_WIDTH) {
		Organism* o = city->getAt(x + 1, y);
		if (o != nullptr && o->getType() == HUMAN) {
			victims.push_back(o);
		}
	}

	//Southeast
	if ((x + 1) < CITY_WIDTH && (y + 1) < CITY_HEIGHT) {
		Organism* o = city->getAt(x + 1, y + 1);
		if (o != nullptr && o->getType() == HUMAN) {
			victims.push_back(o);
		}
	}

	//South
	if ((y + 1) < CITY_HEIGHT) {
		Organism* o = city->getAt(x, y + 1);
		if (o != nullptr && o->getType() == HUMAN) {
			victims.push_back(o);
		}
	}

	//Southwest
	if ((x - 1) >= 0 && (y + 1) < CITY_HEIGHT) {
		Organism* o = city->getAt(x - 1, y + 1);
		if (o != nullptr && o->getType() == HUMAN) {
			victims.push_back(o);
		}
	}

	//West
	if ((x - 1) >= 0) {
		Organism* o = city->getAt(x - 1, y);
		if (o != nullptr && o->getType() == HUMAN) {
			victims.push_back(o);
		}
	}

	//Northwest
	if ((x - 1) >= 0 && (y - 1) >= 0) {
		Organism* o = city->getAt(x - 1, y - 1);
		if (o != nullptr && o->getType() == HUMAN) {
			victims.push_back(o);
		}
	}

	//Select a victim
	if (victims.size() > 0) {
		int lucky = rand() % victims.size();
		return victims[lucky];
	}

	return nullptr;
}

/**
 * Insturct a zombie to eat its poor victim.
 * @param o The organism to eat.
 */
void Zombie::eatVictim(Organism* o) {
	int v_x = o->getX();
	int v_y = o->getY();
	int old_x = x;
	int old_y = y;

	delete o;

	setPosition(v_x, v_y);
	city->putAt(v_x, v_y, this);
	city->clearAt(old_x, old_y);
}