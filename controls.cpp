#include "controls.h"

//Working variables --------------------------------------

//Camera move
static bool mouse_drag_toggle = false;
static sf::Vector2f mouse_drag_start_location(0,0);
static sf::Vector2f view_center_start_location(0,0);

//Tool mode
static std::string tool_array[] = {"ADD OBJECT", "ADD SYSTEM"};
static int current_tool = 1;
static bool tool_toggle = false;
static sf::Vector2f tool_vector2f_0(0,0);
static sf::Vector2f tool_vector2f_1(0,0);

//--------------------------------------------------------

void control_reset_working_variables(){
	mouse_drag_toggle = false;
	mouse_drag_start_location = sf::Vector2f(0,0);
	view_center_start_location = sf::Vector2f(0,0);

	tool_toggle = false;
	tool_vector2f_0 = sf::Vector2f(0,0);
}


void control_event_handler(sf::Event &event, sf::RenderWindow &window, sf::View &camera, World &world){

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

			break;
		}


		case (sf::Event::KeyPressed): //Keyboard shortcuts
		{

			if (event.key.code == sf::Keyboard::Escape) //Quit game
			{
				window.close();
				return;
			}

			if (event.key.code == sf::Keyboard::A) //Iterate through tools
			{
				control_reset_working_variables();
				if (current_tool < 2) current_tool++;
				if (current_tool >= 2) current_tool = 0;
				std::cout << "Current tool: "  << current_tool << " ," << tool_array[current_tool] << std::endl;
			}

			break;
		}

	}


}

void control_drag_camera(sf::Event &event, sf::RenderWindow &window, sf::View &camera){

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

void control_use_tool(sf::Event &event, sf::RenderWindow &window, sf::View &camera, World &world){

	if (current_tool == 0) //Adds planet
	{
		control_add_object(event, window, camera, world);
	}

	if (current_tool == 1) //Adds system
	{
		control_add_system(event, window, camera, world);
	}

}

void control_add_object(sf::Event &event, sf::RenderWindow &window, sf::View &camera, World &world){

	//Registers first mousepress location
	if (!tool_toggle)
	{
		tool_vector2f_0 = window.mapPixelToCoords(sf::Mouse::getPosition(window));
		tool_toggle = true;
		return;
	}

	//Creates object on second press
	if (tool_toggle)
	{

		sf::Vector2f mouse_delta = window.mapPixelToCoords(sf::Mouse::getPosition(window)) - tool_vector2f_0;
		mouse_delta.x *= -CONTROL_ADD_PLANET_SPEED_MULTIPLIER;
		mouse_delta.y *= -CONTROL_ADD_PLANET_SPEED_MULTIPLIER;

		Object* new_object = new Object(tool_vector2f_0,mouse_delta,5);
		new_object->light_emitter = false;
		new_object->color = sf::Color(150,150,200);
		world.add_object(new_object);

		control_reset_working_variables();
	}
}

void control_add_system(sf::Event &event, sf::RenderWindow &window, sf::View &camera, World &world){

	//Registers first mousepress location
	if (!tool_toggle)
	{
		tool_vector2f_0 = window.mapPixelToCoords(sf::Mouse::getPosition(window));
		tool_toggle = true;
		std::cout << "FIRST CLICK" << std::endl;
		return;
	}

	//Creates system on second press
	if (tool_toggle)
	{
		std::cout << "SECOND CLICK" << std::endl;
		tool_vector2f_1 = window.mapPixelToCoords(sf::Mouse::getPosition(window)) - tool_vector2f_0;
		float rad_max = euc_norm(tool_vector2f_1);

		float delta_angle = 2*PI / 200;
		int i = 0;

		for (float angle = 0; angle < 2*PI; angle += delta_angle)
		{
			std::cout << "CREATING OBJECT " << ++i << std::endl;
			Object* new_object = new Object(tool_vector2f_0,sf::Vector2f(0,0),0.1);

			float dist = random_float(0,rad_max);
			new_object->pos = new_object->pos + p2v(dist,angle);

			new_object->light_emitter = false;
			new_object->color = sf::Color(150,150,150);
			world.add_object(new_object);
		}

		control_reset_working_variables();
	}

}

void control_draw_tool_helpers(sf::RenderWindow &window){

	if (current_tool == 0 && tool_toggle) //Draws add planet line
	{
		draw_line(tool_vector2f_0,window.mapPixelToCoords(sf::Mouse::getPosition(window)),window);
	}

}
