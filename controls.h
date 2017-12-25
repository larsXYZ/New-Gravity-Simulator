#ifndef _CONTROLS_
#define _CONTROLS_

/*

		CONTROL HANDLER
			-Research shows that being able to control things increases experienced joy

*/

//Dependencies
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

//Functions
void control_event_handler(sf::Event &event, sf::RenderWindow &window, sf::View &camera); //Main control function
void control_drag_camera(sf::Event &event, sf::RenderWindow &window, sf::View &camera); //Handles dragging of the camera

#endif
