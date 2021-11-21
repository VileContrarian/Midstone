#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Vector.h"
using namespace MATH;

class Actor
{
public:
	Actor(double p_x, double p_y, Vec2 accel_, float mass_, SDL_Texture* p_tex);
	float getX();
	float getY();
	SDL_Texture* getTex();
	SDL_Rect getCurrentFrame();
private:
	float x, y;
	SDL_Rect currentFrame;
	SDL_Texture* tex;
};