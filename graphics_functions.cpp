//Dependencies
#include "graphics_functions.h"

#include <iostream>

void draw_object(sf::RenderWindow* target_window, Object* render_object)
{

	//Constructs circle
	sf::CircleShape circle;
	circle.setRadius(render_object->rad);
	circle.setPosition(render_object->pos);
	circle.setFillColor(sf::Color(120,170,120,255));
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

void draw_light_single_object(sf::RenderWindow* target_window, Object *p)
{
	//Iterates through object list and draws their light on screen
	if (!p->light_emitter) return;
	
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

		//If there is no nearby elements we use the normal method
		if (close_objects.size() == 0) draw_light_single_object(target_window, p);

		//Sort elements after distance
		sort_shadows_dist(close_objects);

		//Collapse shadows, deal with eclipses, etc.
		collapse_shadows(close_objects);

		//Sort elements after angle
		sort_shadows_angle(close_objects);
	
		//Calculating angle difference
		float angle_delta = 2*PI/(LIGHT_VERTEX_COUNT-2);
		float curr_angle = -PI;
		float curr_dist;
		float max_range = light_get_range(p);
		int shadow_index = 0;

		//Create and populate light_vertex array
		sf::VertexArray light_array(sf::TrianglesFan);
		light_array.append(sf::Vertex(p->pos, sf::Color(255,255,255,160)));
		light_array.append(sf::Vertex(p->pos+sf::Vector2f(max_range,0), sf::Color(255,255,255,0)));

		while (curr_angle < PI)
		{
	
			Shadow next_shadow = close_objects[shadow_index];		
		
			if (curr_angle + angle_delta >= next_shadow.left && shadow_index < close_objects.size())
			{
				
				curr_angle = next_shadow.left;
				curr_dist = max_range;
				light_array.append(sf::Vertex(p->pos-sf::Vector2f(curr_dist*cos(curr_angle),curr_dist*sin(curr_angle)), sf::Color(255,255,255,0)));
				
				curr_dist = next_shadow.dist;
				light_array.append(sf::Vertex(p->pos-sf::Vector2f(curr_dist*cos(curr_angle),curr_dist*sin(curr_angle)), sf::Color(255,255,255,160-160*(next_shadow.dist/light_get_range(p)))));

				curr_angle = next_shadow.right;
				light_array.append(sf::Vertex(p->pos-sf::Vector2f(curr_dist*cos(curr_angle),curr_dist*sin(curr_angle)), sf::Color(255,255,255,160-160*(next_shadow.dist/light_get_range(p)))));				
				shadow_index++;

				if (close_objects[shadow_index].left != curr_angle)
				{
					curr_dist = max_range;
					light_array.append(sf::Vertex(p->pos-sf::Vector2f(curr_dist*cos(curr_angle),curr_dist*sin(curr_angle)), sf::Color(255,255,255,0)));				
				}
			}
			else
			{
				curr_dist = max_range;
				light_array.append(sf::Vertex(p->pos-sf::Vector2f(curr_dist*cos(curr_angle),curr_dist*sin(curr_angle)), sf::Color(255,255,255,0)));
				curr_angle += angle_delta;
			}
		}
		if (curr_angle != PI) light_array.append(sf::Vertex(p->pos+sf::Vector2f(light_get_range(p),0), sf::Color(255,255,255,0)));

		//Draw vertexArray
		target_window->draw(light_array);
		
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

void sort_shadows_dist(std::vector<Shadow> &shadows)
{
	for (int i = 1; i < shadows.size(); i++)
	{
		int q = i;
		int r = i-1;
		while(shadows[q].dist < shadows[r].dist && r >= 0)
		{
			//Swap
			Shadow midl = shadows[q];
			shadows[q] = shadows[r];
			shadows[r] = midl;

			//One step down
			q = r;
			r--;
		}
	}
}
void sort_shadows_angle(std::vector<Shadow> &shadows)
{
	for (int i = 1; i < shadows.size(); i++)
	{
		int q = i;
		int r = i-1;
		while(shadows[q].left < shadows[r].left && r >= 0)
		{
			//Swap
			Shadow midl = shadows[q];
			shadows[q] = shadows[r];
			shadows[r] = midl;

			//One step down
			q = r;
			r--;
		}
	}
}
