#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

#include "object.h"
#include "world.h"
#include "graphics_functions.h"
#include "math_functions.h"
#include "util_functions.h"

//RenderWindow and viewport
sf::RenderWindow window(sf::VideoMode(1600, 900), "Gravity Simulator 1.2");
sf::View view1(sf::FloatRect(0 , 0, 1600, 900));

//World
World test_world;

int main()
{

	//Test objects
	Object* new_object = new Object(sf::Vector2f(800,450),sf::Vector2f(0.03,0),1000);
	test_world.add_object(new_object);


	while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
	
		collision_detection(test_world.object_list);
		draw_light(&window,test_world);
		draw_world(&window,test_world);
		leapfrog_integrator(test_world.object_list);
		//view1.setCenter(test_object->pos);

		window.setView(view1);
		window.display();
		window.clear();

	}
}
