#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

#include "Window.h"
#include "Actor.h"

int main(int argc, char* args[])
{
	if (SDL_Init(SDL_INIT_VIDEO) > 0)
		std::cout << "HEY.. SDL_Init HAS FAILED. SDL_ERROR: " << SDL_GetError() << std::endl;

	if (!(IMG_Init(IMG_INIT_PNG)))
		std::cout << "IMG_init has failed. Error: " << SDL_GetError() << std::endl;

	RenderWindow window("MidstonePlatformer", 1280, 720);

	SDL_Texture* Background = window.loadTexture("assets/Starmap.png");

	SDL_Texture* ground = window.loadTexture("assets/ground_grass_1.png");

	Vec2 PAccel;
	PAccel.set(0,0);

	//Actor block = Actor(0, 0, PAccel, 0.0f, ground);
	Actor entities[4] = { Actor(0, 0,PAccel,0.0f, ground),
						  Actor(30, 0,PAccel,0.0f, ground),
						  Actor(30, 30,PAccel,0.0f, ground),
						  Actor(30, 60,PAccel,0.0f, ground) };

	bool gameRunning = true;

	SDL_Event event;

	while (gameRunning)
	{
		// Get our controls and events
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				gameRunning = false;
		}

		window.clear();
		window.renderBack(Background);

		for (int i = 0; i < 4; i++)
		{
			window.renderAct(entities[i]);
		}
		window.display();

	}

	window.cleanUp();
	SDL_Quit();

	return 0;
}