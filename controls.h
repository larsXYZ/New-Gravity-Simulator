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

#include "world.h"
#include "object.h"
#include "constants.h"
#include "graphics_functions.h"
#include "math_functions.h"
#include "util_functions.h"

//Functions
void control_event_handler(sf::Event &event, sf::RenderWindow &window, sf::View &camera, World &world); //Main control function
void control_drag_camera(sf::Event &event, sf::RenderWindow &window, sf::View &camera); //Handles dragging of the camera
void control_draw_tool_helpers(sf::RenderWindow &window); //Draws helper graphics for tools
void control_reset_working_variables(); //Resets internal working variables

void control_use_tool(sf::Event &event, sf::RenderWindow &window, sf::View &camera, World &world); //Uses current tool
void control_add_object(sf::Event &event, sf::RenderWindow &window, sf::View &camera, World &world); //Adds object
void control_add_system(sf::Event &event, sf::RenderWindow &window, sf::View &camera, World &world); //Adds system of small object

#endif
