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
sf::RenderWindow window(sf::VideoMode(1920, 1080), "Gravity Simulator 1.2",sf::Style::Fullscreen);
sf::View view1(sf::FloatRect(0 , 0, 1920, 1080));

//World
World test_world;

int main()
{
	view1.zoom(1);

	//Test objects
	Object* new_object = new Object(sf::Vector2f(5000,5000),sf::Vector2f(0,0),200000);
	new_object->light_emitter = true;
	new_object->color = sf::Color(255,220,200);
	test_world.add_object(new_object);

	Object* new_object2 = new Object(sf::Vector2f(5000,12000),sf::Vector2f(25, 0),200);
	new_object2->color = sf::Color(70,70,70);
	test_world.add_object(new_object2);
	
	Object* new_object3 = new Object(sf::Vector2f(4750,11500),sf::Vector2f(28, 0),1);
	new_object3->color = sf::Color(40,40,40);
	test_world.add_object(new_object3);

	view1.setCenter(new_object2->pos + sf::Vector2f(2000,-300));




	while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }


		collision_detection(test_world.object_list);
		
		draw_world(&window,test_world);
		draw_light_w_shadow(&window,test_world);
		draw_shine(&window,test_world);
		
		leapfrog_integrator(test_world.object_list);

		window.setView(view1);
		window.display();
		window.clear();

	}
}
