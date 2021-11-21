#include "Actor.h"
#include <SDL.h>
#include <SDL_image.h>

Actor::Actor(double p_x, double p_y, Vec2 accel_, float mass_, SDL_Texture* p_tex)
{
	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = 32;
	currentFrame.h = 32;
}

float Actor::getX()
{
	return x;
}
float Actor::getY()
{
	return y;
}

SDL_Texture* Actor::getTex()
{
	return tex;
}

SDL_Rect Actor::getCurrentFrame()
{
	return currentFrame;
}
