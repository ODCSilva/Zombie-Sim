#ifndef CITY_H
#define CITY_H
#include "Organism.h"
#include "Human.h"
#include <iostream>

struct Tile {
	Organism *organism;

	Tile() {
		organism = nullptr;
	}
};

class City {
protected:
	Tile **tiles;

public:
	City();
	virtual ~City();
	void putAt(int, int, Organism*);
	Organism* getAt(int, int);
	void clearAt(int, int);
	void populate();
	friend std::wostream& operator<<(std::wostream&, City&);
	void move();
	bool checkForExtinction();
};
#endif // !CITY_H

