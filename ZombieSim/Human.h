#ifndef HUMAN_H
#define HUMAN_H
#include "Organism.h"
#include <iostream>

class Human : public Organism {
private:
	int recruitCounter;
public:
	Human();
	Human(City*, int, int);
	int getType();
	virtual ~Human();
	void move();
	virtual std::wostream& print(std::wostream&) const;
	friend std::wostream& operator<<(std::wostream &out, const Human &human);
	void moveRandomly();
	void act();
	void recruit();
};
#endif // !HUMAN_H

