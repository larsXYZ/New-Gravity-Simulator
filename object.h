#ifndef _OBJECT_
#define _OBJECT_

/*

		ASTRONOMICAL OBJECT
			-The universe is filled with these

*/

//Dependencies
#include <SFML/Graphics.hpp>
#include "util_functions.h"
#include "constants.h"

struct Object
{
	
	//Variables
	sf::Vector2f pos;
	sf::Vector2f vel;
	sf::Vector2f acc;
	float rad;
	float mass;
	bool light_emitter;

	//Graphic Variables
	sf::Color color;
	
	//Constructors
	Object();
	Object(sf::Vector2f position, sf::Vector2f velocity, float m);

	//Utilities
	void update_rad(); //Updates radius of object 
	

};

#endif
