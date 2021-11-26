#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Vector.h"
#include "Math.h"
using namespace MATH;

class Actor
{
public:
	Actor(Vector2f p_pos, Vec2 accel_, float mass_, SDL_Texture* p_tex);
	Vector2f& getPos() {
		return pos;
	}
	SDL_Texture* getTex();
	SDL_Rect getCurrentFrame();
private:
	Vector2f pos;
	SDL_Rect currentFrame;
	SDL_Texture* tex;
};