#ifndef _CONTROLS_
#define _CONTROLS_

/*

		ASTRONOMICAL OBJECT
			-The universe is filled with these

*/

//Dependencies
#include <SFML/Graphics.hpp>

//Working variables
bool mouse_drag_toggle = false;

//Functions
void control_event_handler(sf::Event &event, sf::RenderWindow &window, sf::View &camera); //Main control function

#endif
