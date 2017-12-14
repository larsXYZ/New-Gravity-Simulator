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
#include "constants.h"

//Shadows and shadow auxilliary functions
struct Shadow{ float dist; float left; float right; };
void collapse_shadows(std::vector<Shadow> &shadows); //Adds shadow to list of shadow, deals with eclipses etc..
void sort_shadows_dist(std::vector<Shadow> &shadows); //Sorts shadow list based on distance, insertion sort..
void sort_shadows_angle(std::vector<Shadow> &shadows); //Sorts shadow list based on angle, insertion sort..
std::vector<Shadow> get_shadow_list(Object* p, std::vector<Object*> &object_list); 
float light_get_range(Object* render_object); //Returns radius of light

//Functions
void draw_object(sf::RenderWindow* target_window, Object* render_object); //Draws planet on screen
void draw_world(sf::RenderWindow* target_window, World& render_object); //Draws world on screen
void draw_light_single_object(sf::RenderWindow* target_window, Object *p); //Draws lights from single light source, without shadows
void draw_light_single_object_w_shadow(sf::RenderWindow* target_window, Object *p, std::vector<Object*> object_list); //Draws lights from single light source, without shadows
void draw_light_w_shadow(sf::RenderWindow* target_window, World& render_object); //Draws lights with shadows, worst case O(n^3) :(
void draw_light_w_shadow_simple(sf::RenderWindow* target_window, World& render_object); //Simpler version of draw_light_w_shadow()


#endif
