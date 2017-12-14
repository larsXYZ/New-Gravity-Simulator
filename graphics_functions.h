#ifndef _GRAPHICS_FUNCTIONS_
#define _GRAPHICS_FUNCTIONS_

/*

		UTILITY FUNCTIONS FOR DISPLAYING THINGS

*/

//Dependencies
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "object.h"
#include "world.h"
#include "math_functions.h"

//Constants
#define LIGHT_VERTEX_COUNT 50
#define LIGHT_STRENGTH_MULTIPLIER 10

//Shadows and shadow auxilliary functions
struct Shadow{ float dist; float left; float right; };
void collapse_shadows(std::vector<Shadow> &shadows); //Adds shadow to list of shadow, deals with eclipses etc..
void sort_shadows_dist(std::vector<Shadow> &shadows); //Sorts shadow list based on distance, insertion sort..
void sort_shadows_angle(std::vector<Shadow> &shadows); //Sorts shadow list based on angle, insertion sort..

//Functions
void draw_object(sf::RenderWindow* target_window, Object* render_object); //Draws planet on screen
void draw_world(sf::RenderWindow* target_window, World& render_object); //Draws world on screen
void draw_light_single_object(sf::RenderWindow* target_window, Object *p); //Draws lights from single light source, without shadows
void draw_light_w_shadow(sf::RenderWindow* target_window, World& render_object); //Draws lights with shadows
float light_get_range(Object* render_object); //Returns radius of light

#endif
