#ifndef _OBJECT_
#define _OBJECT_

/*

		ASTRONOMICAL OBJECT
			-The universe is filled with these

*/

#include <SFML/Graphics.hpp>

struct Object
{
	
	//Variables
	sf::Vector2f pos;
	sf::Vector2f vel;
	sf::Vector2f acc;
	float rad;
	float mass;

	//Constructors
	Object();
	Object(sf::Vector2f position, sf::Vector2f velocity, float radius);
	

};

#endif
