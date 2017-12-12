#ifndef _WORLD_
#define _WORLD_

/*

		WORLD OBJECT
			-Keeps track of everything in a world

*/

//Dependencies
#include <vector>
#include "object.h"

struct World
{
	//Variables
	std::vector<Object*> object_list;

	//Destructor
	~World();

	//Functions
	void add_object(Object* new_object);

};

#endif
