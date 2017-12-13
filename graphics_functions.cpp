//Dependencies
#include "graphics_functions.h"

#include <iostream>

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
		std::vector<Shadow> close_objects; // {distance, left, right}
		float light_rad = light_get_range(p);
		
		for (int q = 0; q < render_object.object_list.size(); q++)
		{
			Object* t = render_object.object_list[q];
			float d = sqrt(distance2(p,t));

			//Convert to angle data and add to close_objects vector			
			if (i != q && d < light_rad)
			{


				//Angle calculations
				sf::Vector2f pos_diff = p->pos - t->pos;
				float mid_angle = atan2(pos_diff.y,pos_diff.x);
				float radius_angle = atan(t->rad/d);
				float left = (mid_angle - radius_angle);
				float right = (mid_angle + radius_angle);

				//Fix looping issues, split shadow into two.
				
				if (left < -PI)
				{
					Shadow left_data;
					Shadow right_data;
					left_data.dist = d;
					right_data.dist = d;

					left_data.left = left + 2*PI;
					left_data.right = PI;
					right_data.left = -PI;
					right_data.right = right;
					close_objects.push_back(left_data);
					close_objects.push_back(right_data);
				}
				else if (right > PI)
				{
					Shadow left_data;
					Shadow right_data;
					left_data.dist = d;
					right_data.dist = d;

					left_data.left = left;
					left_data.right = PI;
					right_data.left = -PI;
					right_data.right = right - 2*PI;
					close_objects.push_back(left_data);
					close_objects.push_back(right_data);
				}
				else
				{
					//Calculate data and fill close_objects vector
					Shadow data;				
					data.dist = d;
					data.left = left;
					data.right = right;
					close_objects.push_back(data);
				}
				
				
			}
		}

		//Sort elements after distance
		for (int i = 1; i < close_objects.size(); i++)
		{
			int q = i;
			int r = i-1;
			while(close_objects[q].dist < close_objects[r].dist && r >= 0)
			{
				//Swap
				Shadow midl = close_objects[q];
				close_objects[q] = close_objects[r];
				close_objects[r] = midl;

				//One step down
				q = r;
				r--;
			}
		}

		//Collapse shadows, deal with eclipses, etc.
		collapse_shadows(close_objects);

		/*	
		//Debug
		std::cout << "\n" << std::endl;
		for (int i = 0; i < close_objects.size(); i++) std::cout << i << " : " << close_objects[i].dist << " | " << close_objects[i].left << " , " << close_objects[i].right << std::endl;
		std::cout <<" Collapsed: "  <<std::endl;

		
	
		for (int i = 0; i < close_objects.size(); i++) std::cout << i << " : " << close_objects[i].dist << " | " << close_objects[i].left << " , " << close_objects[i].right << std::endl;
		*/		
		for (int i = 0; i < close_objects.size(); i++)
		{
			Shadow s = close_objects[i];
			sf::VertexArray lines(sf::LinesStrip, 2);
			lines[0].position = p->pos;
			lines[1].position = p->pos-sf::Vector2f(s.dist*cos(s.left),s.dist*sin(s.left));
			target_window->draw(lines);

			lines[0].position = p->pos;
			lines[1].position = p->pos-sf::Vector2f(s.dist*cos(s.right),s.dist*sin(s.right));
			target_window->draw(lines);

			lines[0].position = p->pos-sf::Vector2f(s.dist*cos(s.left),s.dist*sin(s.left));
			lines[1].position = p->pos-sf::Vector2f(s.dist*cos(s.right),s.dist*sin(s.right));
			target_window->draw(lines);
		}
		
		
	}
}

void collapse_shadows(std::vector<Shadow> &shadows)
{

	//Five cases, [left eclipsed, right eclipsed, both eclipsed, none eclipsed, bigger than objects above]
	std::vector<Shadow> shadows_collapsed;
	shadows_collapsed.push_back(shadows[0]);
	
	for (int i = 1; i < shadows.size(); i++)
	{	
		Shadow s = shadows[i];
		bool addme =  true;		

		for (int q = 0; q < shadows_collapsed.size(); q++)
		{
			Shadow o = shadows_collapsed[q]; //The shadow above

			if (s.left < o.left && s.right > o.right)
			{
			
				//Splits shadow
				Shadow ls = s;
				Shadow rs = s;
				ls.right = o.left;
				rs.left = o.right;
				//Adds subshadows
				shadows.insert(shadows.begin()+i+1,ls);
				shadows.insert(shadows.begin()+i+1,rs);
				addme = false;
				break;
			
			}

			if (s.left >= o.left && s.left <= o.right) s.left = o.right; 	//Left eclipsed
			if (s.right <= o.right && s.right >= o.left) s.right = o.left; 	//Right eclipsed
		}
		if (s.right > s.left && addme) shadows_collapsed.push_back(s); 	//Not both eclipsed
	}

	shadows = shadows_collapsed;
}

float light_get_range(Object* render_object)
{
	return LIGHT_STRENGTH_MULTIPLIER*render_object->rad;
}
