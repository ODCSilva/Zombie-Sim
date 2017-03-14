#ifndef ZOMBIE_H
#define ZOMBIE_H
#include "Organism.h"
#include <iostream>

class Zombie : public Organism {
private:
	int convertCounter;
	int starveCounter;
public:
	Zombie();
	Zombie(City*, int, int);
	int getType();
	virtual ~Zombie();
	void move();
	virtual std::wostream& print(std::wostream&) const;
	friend std::wostream& operator<< (std::wostream &out, const Zombie &zombie);
	void moveRandomly();
	Organism* findVictim();
	void eatVictim(Organism*);
	void act();
	void convertVictim(Organism*);
	void transform();
};
#endif // !ZOMBIE_H
