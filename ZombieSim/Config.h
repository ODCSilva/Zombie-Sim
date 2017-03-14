#ifndef CONFIG_H
#define CONFIG_H
#include <Windows.h>

/***********************************************
  Configuration file for the simulation.
 **********************************************/
const int CITY_WIDTH = 20;				// Width of city grid
const int CITY_HEIGHT = 20;				// Height of city grid
const int START_ZOMBIE_COUNT = 5;       // Number of starting zombies
const int START_HUMAN_COUNT = 100;      // Number of starting humans
const int HUMAN_RECRUIT_TURNS = 3;      // Turns before humans can recruit
const int ZOMBIE_CONVERT_TURNS = 8;     // Turns before zombies can convert
const int ZOMBIE_STARVE_TURNS = 3;		// Turns before zombies starve
const wchar_t HUMAN_CHAR = L'\u263A';	// Character representing human
const char SPACE_CHAR = ' ';			// Character representing empty space
const wchar_t ZOMBIE_CHAR = L'\u263B';	// Character representing zombies

const double PAUSE_SECONDS = 0.09;		// Interval between ticks
const int ITERATIONS = 1000;			// Maximum number of iterations
const bool SHOW_GRID = false;           // Shows/hide grid

//Colors
//0  = black				//9  = bright blue
//1  = blue					//10 = bright green
//2  = green				//11 = bright turquoise
//3  = turquise				//12 = bright red
//4  = red					//13 = bright pink
//5  = pink					//14 = bright yellow
//6  = yellow				//15 = bright white
//7  = white regular		//16+ = solid blocks
//8  = white pale

const int HUMAN_COLOR = 13;
const int ZOMBIE_COLOR = 2;

/**************************
 Grid stuff...
**************************/
const wchar_t CORNER_TOP_LEFT = L'\u256D';
const wchar_t CORNER_TOP_RIGHT = L'\u256E';
const wchar_t CORNER_BOTTOM_LEFT = L'\u2570';
const wchar_t CORNER_BOTTOM_RIGHT = L'\u256F';
const wchar_t TOP_T = L'\u252C';
const wchar_t SIDES = L'\u2502';
const wchar_t BOTTOM_T = L'\u2534';
const wchar_t MIDDLE_T = L'\u253C';
const wchar_t LEFT_T = L'\u251C';
const wchar_t RIGHT_T = L'\u2524';
const wchar_t HORIZONTAL_LINE = L'\u2500';

class Config {
public:
	static void setColor(int color) {
		HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
		FlushConsoleInputBuffer(hstdout);
		SetConsoleTextAttribute(hstdout, color);
	}
};


#endif // !CONFIG_H

