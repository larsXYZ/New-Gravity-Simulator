#ifndef _OBJECT_
#define _OBJECT_

/*

		ASTRONOMICAL OBJECT
			-The universe is filled with these

*/

//Dependencies
#include <SFML/Graphics.hpp>

//Object constants
#define OBJECT_DENSITY 0.3
#define OBJECT_START_MASS 10

struct Object
{
	
	//Variables
	sf::Vector2f pos;
	sf::Vector2f vel;
	sf::Vector2f acc;
	float rad;
	float mass;
	bool light_emitter;

	//Constructors
	Object();
	Object(sf::Vector2f position, sf::Vector2f velocity, float m);

	//Utilities
	void update_rad(); //Updates radius of object 
	

};

#endif
