#include "math_functions.h"
#include "math.h"

sf::Vector2f acceleration(Object* planet, Object* attractor)
{
	//Calculate distance
	float d2 = pow((planet->pos.x - attractor->pos.x),2) + pow((planet->pos.y - attractor->pos.y),2);
	float d = sqrt(d2);
	sf::Vector2f unit_dist = (planet->pos - attractor->pos)/d;

	//Find acceleration
	return - G * attractor->mass * unit_dist / d2;
}

void euler_integrator(std::vector<Object*> &object_list)
{
	//Calculate acceleration
	for (int i = 0; i < object_list.size(); i++)
	{
		object_list[i]->acc = sf::Vector2f(0,0);
		for (int q = 0; q < object_list.size(); q++)
		{
			//Ignore self
			if (q == i) continue;
			
			//Add acceleration
			object_list[i]->acc += acceleration(object_list[i], object_list[q]);
			
		}
	}

	//Move one timestep
	for (int i = 0; i < object_list.size(); i++)
	{
		object_list[i]->vel += object_list[i]->acc*T;
		object_list[i]->pos += object_list[i]->vel*T;
	}
}

void leapfrog_integrator(std::vector<Object*> &object_list)
{
	
	//Saves a_i
	sf::Vector2f a_i[object_list.size()];

	//Calculate a_i
	for (int i = 0; i < object_list.size(); i++)
	{

		object_list[i]->acc = sf::Vector2f(0,0);
		a_i[i] = sf::Vector2f(0,0);

		for (int q = 0; q < object_list.size(); q++)
		{
			//Ignore self
			if (q == i) continue;

			//Add acceleration
			a_i[i] += acceleration(object_list[i], object_list[q]);
		}

		object_list[i]->acc = a_i[i];
	}

	//Update position
	for (int i = 0; i < object_list.size(); i++)
	{
		object_list[i]->pos.x += object_list[i]->vel.x*T + 0.5*object_list[i]->acc.x*T*T;
		object_list[i]->pos.y += object_list[i]->vel.y*T + 0.5*object_list[i]->acc.y*T*T;
	}

	//Calculate a_i+1
	for (int i = 0; i < object_list.size(); i++)
	{
		object_list[i]->acc = sf::Vector2f(0,0);
		for (int q = 0; q < object_list.size(); q++)
		{
			//Ignore self
			if (q == i) continue;

			//Add acceleration
			object_list[i]->acc += acceleration(object_list[i], object_list[q]);
		}
	}
	
	//Update velocity
	for (int i = 0; i < object_list.size(); i++)
	{
		object_list[i]->vel.x += (a_i[i].x+object_list[i]->acc.x)*T*0.5;
		object_list[i]->vel.y += (a_i[i].y+object_list[i]->acc.y)*T*0.5;
	}

}

void collision_detection(std::vector<Object*> &object_list)
{

	std::vector<Object*>::iterator it = object_list.begin();

	while(it != object_list.end())
	{
		//We have not collided yet
		bool collided = false;
		
		//Check for all other objects
		for (int q = 0; q < object_list.size(); q++)
		{
			
			//The objects we check
			Object* p = *it;
			Object* t = object_list[q];

			//Ignore self
			if (p->pos == t->pos) continue;
	
			//Check distance
			float d = sqrt((p->pos-t->pos).x*(p->pos-t->pos).x + (p->pos-t->pos).y*(p->pos-t->pos).y);
			
			//Handle eventual collision
			if (d <= p->rad + t->rad && p->mass <= t->mass)
			{
				collided = true;
				t->mass += p->mass; //Transfer mass
				t->vel.x = (t->mass*t->vel.x + p->mass*p->vel.x)/(t->mass+p->mass); //Transfer momentum
				t->vel.y = (t->mass*t->vel.y + p->mass*p->vel.y)/(t->mass+p->mass); 
				delete p; //Unallocate memory
				break;
			}
			
		}
		
		//Delete object from object_list
		if(collided) it = object_list.erase(it);
		else ++it;

		}
}
