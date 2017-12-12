//Dependencies
#include "graphics_functions.h"

void draw_object(sf::RenderWindow* target_window, Object* render_object)
{

	//Constructs circle
	sf::CircleShape circle;
	circle.setRadius(render_object->rad);
	circle.setPosition(render_object->pos);
	circle.setFillColor(sf::Color(120,120,120,255));
	circle.setOrigin(render_object->rad,render_object->rad);
	circle.setPointCount(30);

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
		if (!p->light_emitter) continue;
		
		//Calculating angle difference
		float angle_delta = 2*PI/(LIGHT_VERTEX_COUNT-2);
		float angle = 0;

		//Create and populate light_vertex array
		sf::Vertex light_array[LIGHT_VERTEX_COUNT];
		light_array[0] = sf::Vertex(p->pos, sf::Color::White);
		for (int i = 1; i < LIGHT_VERTEX_COUNT; i++)
		{
			light_array[i] = sf::Vertex(p->pos + sf::Vector2f(light_get_range(p)*cos(angle),light_get_range(p)*sin(angle)), sf::Color(0,0,0,0));
			angle += angle_delta;
		}

		target_window->draw(light_array, LIGHT_VERTEX_COUNT, sf::TrianglesFan);
	}
}

void draw_light_w_shadow(sf::RenderWindow* target_window, World& render_object)
{
	//Iterates through object list and draws their light on screen
	for (int i = 0; i < render_object.object_list.size(); i++)
	{
		//Check if this object is a light emitter
		Object* p = render_object.object_list[i];
		if (!p->light_emitter) continue;		

		//Filter out all other objects that are too far away
		std::vector<float*> close_objects; // {distance, bigger_than_angle, smaller_than_angle}
		float light_rad = light_get_range(p);

		for (int q = 0; q < render_object.object_list.size(); q++)
		{
			Object* t = render_object.object_list[q];
			float d = sqrt(distance2(p,t));
			if (i != q && d < light_rad)
			{
				//Calculate data and fill close_objects vector
				float data[3];
				data[0] = d;

				//Angle calculations
				sf::Vector2f pos_diff = p->pos - t->pos;
				float mid_angle = atan2(pos_diff.y,pos_diff.x);
				float radius_angle = atan(t->rad/d);
				data[1] = mid_angle - radius_angle;
				data[2] = mid_angle + radius_angle;				

				close_objects.push_back(data);
			}
		}

		for (int q = 0; q < close_objects.size(); q++)
		{
			float* data = close_objects[i];
			//Show objects in range
			sf::VertexArray lines(sf::LinesStrip, 2);
			lines[0].position = p->pos;
			lines[1].position = sf::Vector2f(p->pos.x-cos(data[1])*data[0],p->pos.y-sin(data[1])*data[0]);
			target_window->draw(lines);

			lines[0].position = p->pos;
			lines[1].position = sf::Vector2f(p->pos.x-cos(data[2])*data[0],p->pos.y-sin(data[2])*data[0]);
			target_window->draw(lines);
		}

	}
}

float light_get_range(Object* render_object)
{
	return LIGHT_STRENGTH_MULTIPLIER*render_object->rad;
}
