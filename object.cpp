#include "object.h"

Object::Object()
{

	//Applying values
	pos = sf::Vector2f(0,0);
	vel = sf::Vector2f(0,0);
	rad = 10;
	mass = 10;

}

Object::Object(sf::Vector2f position, sf::Vector2f velocity, float radius)
{

	//Applying values
	pos = position;
	vel = velocity;
	rad = radius;
	mass = 10;
	
}
