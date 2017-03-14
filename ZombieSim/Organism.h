#ifndef ORGANISM_H
#define ORGANISM_H
#include <iostream>

class City;

enum { HUMAN, ZOMBIE };

class Organism {
protected:
	int x;
	int y;
	City* city;
	int type;
	bool moved;
public:
	Organism();
	virtual ~Organism();
	virtual void move() = 0;
	virtual void act() = 0;
	void setMoved(bool);
	bool getMoved();
	int getX();
	int getY();
	virtual std::wostream& print(std::wostream&) const;
	virtual int getType();
	void setPosition(int, int);
    friend std::wostream& operator<< (std::wostream&, const Organism&);
};

#endif // !ORGANISM_H
