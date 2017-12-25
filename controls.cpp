#include "controls.h"

void control_event_handler(sf::Event &event, sf::RenderWindow &window, sf::View &camera)
{

	switch (event.type)
	{

		case (sf::Event::Closed): //Ends game	
		{
			window.close();
			return;
		}

		case (sf::Event::MouseButtonPressed): //Mouse press
		{
			if (event.mouseButton.button == sf::Mouse::Right)
			{
				camera.setCenter(sf::Vector2f(sf::Mouse::getPosition(window)));

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
