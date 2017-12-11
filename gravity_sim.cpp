#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

#include "object.h"
#include "world.h"
#include "graphics_functions.h"
#include "math_functions.h"
#include "util_functions.h"

//RenderWindow and viewport
sf::RenderWindow window(sf::VideoMode(1600, 900), "My window");
sf::View view1(sf::FloatRect(0, 0, 1600, 900));

int main()
{

	//Test objects
	World test_world;
	/*Object* test_object = new Object(sf::Vector2f(800,450),sf::Vector2f(0,0),100.0);
	Object* test_object2 = new Object(sf::Vector2f(500,450),sf::Vector2f(0,-0.24),10.0);
	Object* test_object3 = new Object(sf::Vector2f(600,450),sf::Vector2f(0,0.325),7.0);

	test_object->mass = 100;
	test_object2->mass = 1;
	test_object3->mass = 1;
	
	test_world.add_object(test_object);
	test_world.add_object(test_object2);
	test_world.add_object(test_object3);
	*/

	for (int i = 0; i < 50; i++)
	{
		Object* new_object = new Object(sf::Vector2f(random_int(0,1600),random_int(0,900)),sf::Vector2f(random_float(-0.2,0.2),random_float(-0.2,0.2)),5.0);
		new_object->mass = random_float(0,50);
		test_world.add_object(new_object);
	}

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
		leapfrog_integrator(test_world.object_list);
		//view1.setCenter(test_object->pos);

		window.setView(view1);
		window.display();
		window.clear();		

	}
}
