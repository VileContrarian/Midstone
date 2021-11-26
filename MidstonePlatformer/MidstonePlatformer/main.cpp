#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>

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

	//Actor entities[4] = { Actor(0, 0,PAccel,0.0f, ground),
	//					  Actor(30, 0,PAccel,0.0f, ground),
	//					  Actor(30, 30,PAccel,0.0f, ground),
	//					  Actor(30, 60,PAccel,0.0f, ground) };

	//Dynamic version of the actors array (Tanner)
	std::vector<Actor> entitiees = { Actor(Vector2f(0, 0),PAccel,0.0f, ground),
									 Actor(Vector2f(30, 0),PAccel,0.0f, ground),
								     Actor(Vector2f(30, 30),PAccel,0.0f, ground),
									 Actor(Vector2f(30, 60),PAccel,0.0f, ground) };;
	{
		Actor william(Vector2f(100, 50), PAccel, 0.0f, ground);

		entitiees.push_back(william);
	}
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

		for (Actor& e : entitiees)
		{
			window.renderAct(e);
		}
		window.display();

	}

	window.cleanUp();
	SDL_Quit();

	return 0;
}