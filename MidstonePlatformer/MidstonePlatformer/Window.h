#pragma once
#include <SDL.h>
#include <SDL_image.h>

#include "Actor.h"

class RenderWindow
{
public:
	RenderWindow(const char* p_title, int p_w, int p_h);
	SDL_Texture* loadTexture(const char* p_filePath);
	void cleanUp();
	void clear();
	void renderBack(SDL_Texture* p_tex);
	void renderAct(Actor& p_entity);
	void display();
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
};