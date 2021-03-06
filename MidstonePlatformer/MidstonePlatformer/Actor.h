#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Vector.h"
#include "Math.h"
#include "Collider.h"
using namespace MATH;

class Actor
{
public:
	Actor(Vector2f p_pos, float mass_, SDL_Texture* p_tex);
	Actor(Vector2f p_pos, float mass_, int EntityHealth_, SDL_Texture* p_tex);
	Vector2f& getPos() {
		return pos;
	}

	SDL_Texture* getTex();
	SDL_Rect getCurrentFrame();

	int EntityHealth;

	void SetFrame(int x_, int y_, int w_, int h_);

	void UpdatePos(Vector2f vel);
	
protected:
	Vector2f pos;
	SDL_Rect currentFrame;
	SDL_Texture* tex;
};