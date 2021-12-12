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
	using Actor::Actor;
	/*Player(Vector2f p_pos, float mass_, SDL_Texture* p_tex);
	Vector2f& getPos() {
		return pos;
	}*/
	void Update();
protected:
	std::string pName;

};