#pragma once
#include <SDL.h>
#include <SDL_image.h>

#include "Actor.h"

class RenderWindow
{
public:
	RenderWindow(const char* p_title, int p_w, int p_h);
	SDL_Texture* loadTexture(const char* p_filePath);

	int getRefreshRate();

	void cleanUp();
	void clear();
	void renderBack(SDL_Texture* p_tex);
	void renderAct(Actor& p_entity);
	void display();

	SDL_Renderer* renderer;
private:
	SDL_Window* window;
	
};