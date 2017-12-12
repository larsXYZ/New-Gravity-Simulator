//Dependencies
#include "object.h"

Object::Object()
{

	//Applying values
	pos = sf::Vector2f(0,0);
	vel = sf::Vector2f(0,0);
	mass = OBJECT_START_MASS;
	light_emitter = false;
	update_rad();

}

Object::Object(sf::Vector2f position, sf::Vector2f velocity, float m)
{

	//Applying values
	pos = position;
	vel = velocity;
	mass = m;
	light_emitter = false;
	update_rad();
	
}

void Object::update_rad()
{
	rad = cbrt(mass)/OBJECT_DENSITY;
}
