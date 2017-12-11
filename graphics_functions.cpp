#include "graphics_functions.h"

void draw_object(sf::RenderWindow* target_window, Object* render_object)
{

	//Constructs circle
	sf::CircleShape circle;
	circle.setRadius(render_object->rad);
	circle.setPosition(render_object->pos);
	circle.setFillColor(sf::Color(0,0,0,0));
	circle.setOutlineColor(sf::Color::White);
	circle.setOutlineThickness(2);
	circle.setOrigin(render_object->rad,render_object->rad);

	//Draws on window
	target_window->draw(circle);
}

void draw_world(sf::RenderWindow* target_window, World& render_object)
{

	//Iterates through object list and draws them on screen
	for (int i = 0; i < render_object.object_list.size(); i++)
	{
		draw_object(target_window,render_object.object_list[i]);
	}

}
