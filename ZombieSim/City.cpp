#include "City.h"
#include "Human.h"
#include "Zombie.h"
#include "Config.h"
#include <vector>
#include <cstdlib>
#include <time.h>
#include <io.h>
#include <fcntl.h>
using namespace std;

/**
 * Constructor.
 */
City::City() {
	_setmode(_fileno(stdout), _O_U16TEXT);

	tiles = new Tile*[CITY_WIDTH];
	for (int i = 0; i < CITY_WIDTH; i++) {
		tiles[i] = new Tile[CITY_HEIGHT];
	}

	populate();
}

/**
 * Destructor.
 */
City::~City() {
	for (int i = 0; i < CITY_WIDTH; i++) {
		delete[] tiles[i];
	}

	delete[] tiles;
}

/**
 * Put organism on the board at x, y location.
 */
void City::putAt(int x, int y, Organism *organism) {
	tiles[x][y].organism = organism;
}

/**
 * Get organism at x, y location.
 * @return pointer to organism
 */
Organism* City::getAt(int x, int y) {
	return tiles[x][y].organism;
}


/**
 * Clear organism (assign nullptr) at x, y location.
 */
void City::clearAt(int x, int y) {
	tiles[x][y].organism = nullptr;
}

/**
 * Pupulate the board with organisms.
 */
void City::populate() {

	int count = 0;
	int x, y;

	srand((unsigned int)time(NULL));

	//Humans first
	while (count < START_HUMAN_COUNT) {
		x = rand() % CITY_WIDTH;
		y = rand() % CITY_HEIGHT;

		// Already occupied?
		if (getAt(x, y) == nullptr) {
			Human *h = new Human(this, x, y);
			putAt(x, y, h);
			count++;
		}
	}

	count = 0;

	// Zombes
	while (count < START_ZOMBIE_COUNT) {
		x = rand() % CITY_WIDTH;
		y = rand() % CITY_HEIGHT;

		if (getAt(x, y) == nullptr) {
			Zombie *h = new Zombie(this, x, y);
			putAt(x, y, h);
			count++;
		}
	}
}

/**
 * Overriden << operator.
 * @return Output stream
 */
wostream& operator<<(wostream& out, City& city) {

	Config::setColor(8);

	if (SHOW_GRID) {
		out << CORNER_TOP_LEFT << HORIZONTAL_LINE;

		for (int i = 1; i < CITY_WIDTH; i++) {
			out << TOP_T << HORIZONTAL_LINE;
		}

		out << CORNER_TOP_RIGHT << "\n";
	}

	for (int y = 0; y < CITY_HEIGHT; y++) {
		for (int x = 0; x < CITY_WIDTH; x++) {
			
			if (city.getAt(x, y) != nullptr) {
				if (SHOW_GRID)
					out << SIDES;

				out << *city.getAt(x, y);
			}
			else {
				if (SHOW_GRID)
					out << SIDES;

				out << ' ';
			}
		}

		if (SHOW_GRID) {
			out << SIDES << "\n";

			if (y < CITY_HEIGHT - 1) {
				out << LEFT_T << HORIZONTAL_LINE;

				for (int i = 1; i < CITY_WIDTH; i++) {
					out << MIDDLE_T << HORIZONTAL_LINE;
				}
				out << RIGHT_T << "\n";
			}
		}
		else {
			out << "\n";
		}
	}

	if (SHOW_GRID) {
		out << CORNER_BOTTOM_LEFT << HORIZONTAL_LINE;

		for (int i = 1; i < CITY_WIDTH; i++) {
			out << BOTTOM_T << HORIZONTAL_LINE;
		}

		out << CORNER_BOTTOM_RIGHT;
	}

	return out;
}

/**
 * Iterate through all organisms and call their move and act routines.
 */
void City::move() {
	// Let actors move
	for (int x = 0; x < CITY_WIDTH; x++) {
		for (int y = 0; y < CITY_HEIGHT; y++) {
			if (getAt(x, y) != nullptr) {
				getAt(x, y)->move();
			}
		}
	}

	// Let actors do their thing
	for (int x = 0; x < CITY_WIDTH; x++) {
		for (int y = 0; y < CITY_HEIGHT; y++) {
			if (getAt(x, y) != nullptr) {
				getAt(x, y)->act();
			}
		}
	}

	for (int x = 0; x < CITY_WIDTH; x++) {
		for (int y = 0; y < CITY_HEIGHT; y++) {
			if (getAt(x, y) != nullptr) {
				getAt(x, y)->setMoved(false);
			}
		}
	}
}

/**
 * Check for an extinction event.
 * @return True if an extinction event ocurred, false otherwise.
 */
bool City::checkForExtinction() {
	bool zombiesDied = true;
	bool humansDied = true;

	for (int x = 0; x < CITY_WIDTH; x++) {
		for (int y = 0; y < CITY_HEIGHT; y++) {
			Organism* o = getAt(x, y);
			if (o != nullptr) {
				if (o->getType() == ZOMBIE) {
					zombiesDied = false;
				}
				else {
					humansDied = false;
				}
			}
		}
	}

	return (zombiesDied || humansDied);
}