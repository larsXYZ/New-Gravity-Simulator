//Dependencies
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "object.h"
#include "world.h"
#include "graphics_functions.h"
#include "math_functions.h"
#include "util_functions.h"

//RenderWindow and viewport
sf::RenderWindow window(sf::VideoMode(1920, 1080), "Gravity Simulator 1.2", sf::Style::Fullscreen);
sf::View view1(sf::FloatRect(0 , 0, 1920, 1080));

//World
World test_world;

int main()
{

	//Test objects
	Object* new_object = new Object(sf::Vector2f(800,440),sf::Vector2f(0,0),20000);
	new_object->light_emitter = true;
	test_world.add_object(new_object);
	
	Object* new_object2 = new Object(sf::Vector2f(1100,440),sf::Vector2f(0,0),100);
	test_world.add_object(new_object2);
	

	while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
			
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					new_object2->pos = sf::Vector2f(sf::Mouse::getPosition(window));
				}

				if (event.mouseButton.button == sf::Mouse::Right)
				{
					view1.setCenter(sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y);
				}
			}
        }
	
		collision_detection(test_world.object_list);
		draw_light_w_shadow(&window,test_world);
		draw_light(&window,test_world);
		draw_world(&window,test_world);
		//leapfrog_integrator(test_world.object_list);
		//view1.setCenter(test_object->pos);

		window.setView(view1);
		window.display();
		window.clear();

	}
}
