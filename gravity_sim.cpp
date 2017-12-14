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
sf::RenderWindow window(sf::VideoMode(1920, 1080), "Gravity Simulator 1.2");
sf::View view1(sf::FloatRect(0 , 0, 1920, 1080));

//World
World test_world;

int main()
{

	//Test objects
	Object* new_object = new Object(sf::Vector2f(500,350),sf::Vector2f(0,0.002),2000);
	new_object->light_emitter = true;
	test_world.add_object(new_object);

	Object* new_object2 = new Object(sf::Vector2f(1000,350),sf::Vector2f(0,-0.6),20);
	test_world.add_object(new_object2);

	Object* new_object3 = new Object(sf::Vector2f(960,350),sf::Vector2f(0,-0.85),1);
	test_world.add_object(new_object3);



	while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }


		collision_detection(test_world.object_list);
		draw_light_w_shadow_simple(&window,test_world);
		draw_light_w_shadow(&window,test_world);
		draw_world(&window,test_world);

		view1.setCenter(new_object2->pos);
		
		leapfrog_integrator(test_world.object_list);

		window.setView(view1);
		window.display();
		window.clear();

	}
}
