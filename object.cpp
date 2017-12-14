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
	color = random_color(50,190);

}

Object::Object(sf::Vector2f position, sf::Vector2f velocity, float m)
{

	//Applying values
	pos = position;
	vel = velocity;
	mass = m;
	light_emitter = false;
	update_rad();
	color = random_color(50,190);
	
}

void Object::update_rad()
{
	rad = OBJECT_RADIUS_FACTOR*cbrt(mass)/OBJECT_DENSITY;
}
