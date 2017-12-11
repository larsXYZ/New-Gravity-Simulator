#ifndef _GRAPHICS_FUNCTIONS_
#define _GRAPHICS_FUNCTIONS_

/*

		UTILITY FUNCTIONS FOR DISPLAYING THINGS

*/

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "object.h"
#include "world.h"

//Functions
void draw_object(sf::RenderWindow* target_window, Object* render_object); //Displays planet on screen
void draw_world(sf::RenderWindow* target_window, World& render_object); //Displays world on screen

#endif
