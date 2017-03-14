#include "Organism.h"
#include <Windows.h>
using namespace std;

/* Default constructor. */
Organism::Organism() {}

/* Virtual destructor*/
Organism::~Organism() {}

/**
 * Returns this organism's type
 * @return int representing the organism's type
 */
int Organism::getType() {
	return type;
}

/**
 * Set this organism's x, and y coordinates.
 */
void Organism::setPosition(int x, int y) {
	this->x = x;
	this->y = y;
}

/**
 * Helper method to help with output using polymorphism.
 * @return output stream
 */
wostream& Organism::print(wostream& out) const {
	return out;
}

/**
* Overriden << operator.
* @return output stream.
*/
wostream& operator<<(wostream& out, const Organism& o) {
	return o.print(out);
}

/**
 * Getter for the x property
 */
int Organism::getX() {
	return this->x;
}

/**
 * Getter for the y property
 */
int Organism::getY() {
	return this->y;
}

/**
 * Setter for the moved property
 */
void Organism::setMoved(bool moved) {
	this->moved = moved;
}

/**
 * Check if this organism has moved previously on the current term.
 * @return True of the organism has moved, false otherwise.
 */
bool Organism::getMoved() {
	return this->moved;
}