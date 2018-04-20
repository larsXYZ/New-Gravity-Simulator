//Dependencies
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <TGUI/TGUI.hpp>
#include <iostream>
#include "object.h"
#include "world.h"
#include "graphics_functions.h"
#include "math_functions.h"
#include "util_functions.h"
#include "constants.h"
#include "controls.h"

//RenderWindow and viewport
sf::RenderWindow window(sf::VideoMode(SCREEN_RESOLUTION_HORIZONTAL, SCREEN_RESOLUTION_VERTICAL), "Gravity Simulator 1.2");
sf::View camera(sf::FloatRect(0 , 0, SCREEN_RESOLUTION_HORIZONTAL, SCREEN_RESOLUTION_VERTICAL));

//World
World test_world;

int main(){

	camera.zoom(2);
	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);

	//--------------Test objects-------------------
	/*Object* new_object = new Object(sf::Vector2f(500,200),sf::Vector2f(0.5,0.5),20000);
	new_object->light_emitter = true;
	new_object->color = sf::Color(255,220,200);
	test_world.add_object(new_object);*/
	//---------------------------------------------




	while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)){
					control_event_handler(event,window,camera,test_world);
        }

		collision_detection(test_world.object_list);

		draw_world(&window,test_world);
		draw_light_w_shadow(&window,test_world);
		draw_shine(&window,test_world);
		control_draw_tool_helpers(window);

		leapfrog_integrator(test_world.object_list);

		window.setView(camera);
		window.display();
		window.clear();

	}
}
