#include "graphics_functions.h"

void draw_object(sf::RenderWindow* target_window, Object* render_object)
{

	//Constructs circle
	sf::CircleShape circle;
	circle.setRadius(render_object->rad);
	circle.setPosition(render_object->pos);
	circle.setFillColor(sf::Color(100,100,100,255));
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

void draw_light(sf::RenderWindow* target_window, World& render_object)
{
	//Iterates through object list and draws their light on screen
	for (int i = 0; i < render_object.object_list.size(); i++)
	{
		Object* p = render_object.object_list[i];
		
		//Calculating angle difference
		float angle_delta = 2*PI/(LIGHT_VERTEX_COUNT-2);
		float angle = 0;

		//Create and populate light_vertex array
		sf::Vertex light_array[LIGHT_VERTEX_COUNT];
		light_array[0] = sf::Vertex(p->pos, sf::Color::White);
		for (int i = 1; i < LIGHT_VERTEX_COUNT; i++)
		{
			light_array[i] = sf::Vertex(p->pos + sf::Vector2f(LIGHT_STRENGTH_MULTIPLIER*cos(angle),LIGHT_STRENGTH_MULTIPLIER*sin(angle)), sf::Color(0,0,0,0));
			angle += angle_delta;
		}

		target_window->draw(light_array, LIGHT_VERTEX_COUNT, sf::TrianglesFan);
	}
}
