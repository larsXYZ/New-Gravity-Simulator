#ifndef _CONSTANTS_
#define _CONSTANTS_

/*

		CONSTANTS

*/

//-----Graphics-----
#define PLANET_VERTEX_COUNT 60 //How many vertexes the planets are made from
#define LIGHT_VERTEX_COUNT 50 //How many vertexes the light is made from, might vary depending on shadows
#define LIGHT_STRENGTH_MULTIPLIER 30 //Distance multiplier
#define LIGHT_START_ALPHA 40 //Starting alpha for shadow-generating light
#define LIGHT_SHINE_ALPHA 70 //This light penetrates objects
#define LIGHT_SHINE_RANGE 0.4f //Fraction of shadow generating light range

//-----Math-----
#define G 15.f
#define T 0.001f/*0.0002f*/
#define PI 3.14159265359f

//----Objects-----
#define OBJECT_DENSITY 0.3f
#define OBJECT_START_MASS 10
#define OBJECT_RADIUS_FACTOR 5

#endif
