#include "Zombie.h"
#include "Human.h"
#include "City.h"
#include "Config.h"
#include <iostream>
#include <conio.h>
#include <time.h>
using namespace std;


int main() {

	int iterationCounter = 0;
	clock_t current = clock();
	clock_t last = current;
	double elapsed = 0;

	City city;
	wcout << city;

	/**
	 * Begin simulation.
	 */
	while (iterationCounter <= ITERATIONS) {

		current = clock();
		elapsed += (double)(current - last);
		last = current;

		if (elapsed > (double)(PAUSE_SECONDS * CLOCKS_PER_SEC)) {
			system("cls");
			wcout << city << endl;
			wcout << "Iterations: " << iterationCounter << endl;
			city.move();
			elapsed = 0;
			iterationCounter++;

			if (city.checkForExtinction()) {
				wcout << "EXINCTION EVENT!" << endl;
				break;
			}
		}
	}

	// The end ;_;
	wcout << "Finished!";

	_getch();
	return 0;
}