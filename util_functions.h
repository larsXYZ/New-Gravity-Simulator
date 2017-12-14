#ifndef _UTIL_FUNCTIONS_
#define _UTIL_FUNCTIONS_

/*

		UTILITY FUNCTIONS

*/

//Dependencies
#include <SFML/Graphics.hpp>

//Functions
int random_int(int lower, int higher); //Returns random int between lower and higher
float random_float(float lower, float higher); //Returns random float between lower and higher
sf::Color random_color(int min,int max); //Returns random color, rgb value constricted between min & max

#endif
