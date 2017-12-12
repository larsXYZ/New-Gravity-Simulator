//Dependencies
#include <SFML/Graphics.hpp>
#include "world.h"

World::~World()
{
	for (int i = 0; i < object_list.size(); i++)
	{
		delete object_list[i];
	}
}

void World::add_object(Object* new_object)
{
	object_list.push_back(new_object);
}
