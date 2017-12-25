#include "controls.h"

//Working variables --------------------------------------

//Camera move
static bool mouse_drag_toggle = false;
static sf::Vector2f mouse_drag_start_location(0,0);
static sf::Vector2f view_center_start_location(0,0);

//Tool mode
static std::string tool_array[] = {"ADD PLANET"};
static int current_tool = 0;

//--------------------------------------------------------


void control_event_handler(sf::Event &event, sf::RenderWindow &window, sf::View &camera)
{

	//Other
	switch (event.type)
	{

		case (sf::Event::Closed): //Ends game	
		{
			window.close();
			return;
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
	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right && !mouse_drag_toggle)
	{
		mouse_drag_start_location = window.mapPixelToCoords(sf::Mouse::getPosition(window));
		view_center_start_location = camera.getCenter();

		std::cout << "CLICK, at: " << mouse_drag_start_location.x << " " << mouse_drag_start_location.y <<  std::endl;
		mouse_drag_toggle = true;
	}
	else if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Right) && mouse_drag_toggle) mouse_drag_toggle = false;

	if (mouse_drag_toggle)
	{
		sf::Vector2f mouse_delta = window.mapPixelToCoords(sf::Mouse::getPosition(window)) - mouse_drag_start_location;
		mouse_delta.x *= 0.9;
		mouse_delta.y *= 0.9;

		camera.setCenter(view_center_start_location - mouse_delta);
	}
}








