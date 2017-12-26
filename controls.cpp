#include "controls.h"

//Working variables --------------------------------------

//Camera move
static bool mouse_drag_toggle = false;
static sf::Vector2f mouse_drag_start_location(0,0);
static sf::Vector2f view_center_start_location(0,0);

//Tool mode
static std::string tool_array[] = {"ADD PLANET"};
static int current_tool = 0;
static bool tool_toggle = false;

//--------------------------------------------------------


void control_event_handler(sf::Event &event, sf::RenderWindow &window, sf::View &camera, World &world)
{

	//Click -> drag screen
	control_drag_camera(event,window,camera);

	//Other
	switch (event.type)
	{

		case (sf::Event::Closed): //Ends game	
		{
			window.close();
			return;
		}

		case (sf::Event::MouseButtonPressed): //Mousepress
		{
			
			if (event.mouseButton.button == sf::Mouse::Left) //Uses current tool
			{
				control_use_tool(event,window,camera,world);
			}

		}


		case (sf::Event::KeyPressed): //Keyboard shortcuts
		{
		
			if (event.key.code == sf::Keyboard::Escape) //Quit game
			{
				window.close();
				return;
			}

		}

	}	


}

void control_drag_camera(sf::Event &event, sf::RenderWindow &window, sf::View &camera)
{

	//Registers click and position of view and mouse
	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right && !mouse_drag_toggle)
	{
		mouse_drag_start_location = window.mapPixelToCoords(sf::Mouse::getPosition(window));
		view_center_start_location = camera.getCenter();

		std::cout << "CLICK, at: " << mouse_drag_start_location.x << " " << mouse_drag_start_location.y <<  std::endl;
		mouse_drag_toggle = true;
	}
	else if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Right) && mouse_drag_toggle) mouse_drag_toggle = false;

	//Drags screen
	if (mouse_drag_toggle)
	{
		sf::Vector2f mouse_delta = window.mapPixelToCoords(sf::Mouse::getPosition(window)) - mouse_drag_start_location;

		camera.setCenter(view_center_start_location - mouse_delta);
	}
}

void control_use_tool(sf::Event &event, sf::RenderWindow &window, sf::View &camera, World &world)
{

	if (tool_array[current_tool] == "ADD PLANET") //Adds planet
	{
		control_add_planet(event, window, camera, world);
	}

}

void control_add_planet(sf::Event &event, sf::RenderWindow &window, sf::View &camera, World &world)
{

	//Registers first mousepress location
	if (!tool_toggle)
	{
		mouse_drag_start_location = window.mapPixelToCoords(sf::Mouse::getPosition(window));
		tool_toggle = true;
		return;
	}

	//Creates planet on second press
	if (tool_toggle)
	{
		
		sf::Vector2f mouse_delta = window.mapPixelToCoords(sf::Mouse::getPosition(window)) - mouse_drag_start_location;
		mouse_delta.x *= CONTROL_ADD_PLANET_SPEED_MULTIPLIER;
		mouse_delta.y *= CONTROL_ADD_PLANET_SPEED_MULTIPLIER;

		Object* new_object = new Object(mouse_drag_start_location,mouse_delta,5);
		new_object->light_emitter = false;
		new_object->color = sf::Color(150,150,200);
		world.add_object(new_object);

		tool_toggle = false;
	}
}

void control_draw_tool_helpers(sf::RenderWindow &window)
{

	if (tool_array[current_tool] == "ADD PLANET" && tool_toggle) //Draws add planet line
	{
		draw_line(mouse_drag_start_location,window.mapPixelToCoords(sf::Mouse::getPosition(window)),window);
	}

}


