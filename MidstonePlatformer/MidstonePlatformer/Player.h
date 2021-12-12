#pragma once
#include "Actor.h"
#include <SDL.h>
#include <SDL_image.h>
#include "Vector.h"
#include "Math.h"
using namespace MATH;

class Player : public Actor
{
public:
	void Update();
protected:
	std::string pName;

};