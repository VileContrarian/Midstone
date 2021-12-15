#pragma once
#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Vector.h"
#include "Actor.h"
#include "Math.h"
using namespace MATH;

class Collider
{
public :
	Collider();
	bool Collide(Vec4 a, Vec4 b);
	
};