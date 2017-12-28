#ifndef _MATH_FUNCTIONS_
#define _MATH_FUNCTIONS_

/*

		UTILITY FUNCTIONS FOR DOING MATH

*/

//Dependencies
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "object.h"
#include "world.h"
#include "constants.h"

//Basic math functions
float distance2(Object* p1, Object* p2); //Returns the distance^2 between two objects
sf::Vector2f acceleration(Object* planet, Object* attractor); //Returns acceleration between planet
float euc_norm(sf::Vector2f v); //Returns euclidean norm of vector
sf::Vector2f p2v(float r, float angle); //Returns vector

//Integration functions
void euler_integrator(std::vector<Object*> &object_list);
void leapfrog_integrator(std::vector<Object*> &object_list);

//Collision detection
void collision_detection(std::vector<Object*> &object_list); //Checks for collisions, and handles them

#endif
