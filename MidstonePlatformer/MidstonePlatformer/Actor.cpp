#include "Actor.h"
#include <SDL.h>
#include <SDL_image.h>

Actor::Actor(Vector2f p_pos, Vec2 accel_, float mass_, SDL_Texture* p_tex)
:pos(p_pos) , tex(p_tex)
{
	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = 32;
	currentFrame.h = 32;
}

SDL_Texture* Actor::getTex()
{
	return tex;
}

SDL_Rect Actor::getCurrentFrame()
{
	return currentFrame;
}
