#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>

#include "Window.h"
#include "Actor.h"
#include "Player.h"
#include "Utilities.h"

int main(int argc, char* args[])
{
	if (SDL_Init(SDL_INIT_VIDEO) > 0)
		std::cout << "HEY.. SDL_Init HAS FAILED. SDL_ERROR: " << SDL_GetError() << std::endl;

	if (!(IMG_Init(IMG_INIT_PNG)))
		std::cout << "IMG_init has failed. Error: " << SDL_GetError() << std::endl;

	RenderWindow window("MidstonePlatformer", 1280, 720);

	SDL_Texture* Background = window.loadTexture("assets/Starmap.png");
	SDL_Texture* ground = window.loadTexture("assets/ground_grass_1.png");
	SDL_Texture* character = window.loadTexture("assets/char.png");
	SDL_Texture* guy = window.loadTexture("assets/char.png");

	Vec2 PAccel, PSpawn, BAccel,EAceel;
	BAccel.set(0, 0);
	PAccel.set(0, 0);
	EAceel.set(0.3, 0); //step of enemy
	PSpawn.set(0, 115);

	//Actor block = Actor(0, 0, PAccel, 0.0f, ground);

	//Actor entities[4] = { Actor(0, 0,PAccel,0.0f, ground),
	//					  Actor(30, 0,PAccel,0.0f, ground),
	//					  Actor(30, 30,PAccel,0.0f, ground),
	//					  Actor(30, 60,PAccel,0.0f, ground) };

	//Dynamic version of the actors array (Tanner)
	std::vector<Actor> entitiees = { Actor(Vector2f(0, 150),0.0f, ground),
									 Actor(Vector2f(30, 150),0.0f, ground),
									 Actor(Vector2f(90, 130),0.0f, ground),
									 Actor(Vector2f(150, 115),0.0f, ground),
									 Actor(Vector2f(210, 100),0.0f, ground),
									 Actor(Vector2f(265, 85),0.0f, ground),
									 Actor(Vector2f(295, 85),0.0f, ground) };;

	Player william(Vector2f(PSpawn.x, PSpawn.y), 0.0f, character);
	william.SetFrame(0,0,32,40);
	//entitiees.push_back(william);
	Actor enemy(Vector2f(140, 50), 0.0f, guy);
	enemy.SetFrame(0, 0, 30, 35);

	bool gameRunning = true;

	SDL_Event event;

	const float timeStep = 0.01f;
	float accumulator = 0.0f;
	float currentTime = utilities::hireTimeInSeconds();

	while (gameRunning)
	{
		
		int startTicks = SDL_GetTicks();

		float newTime = utilities::hireTimeInSeconds();
		float frameTime = newTime - currentTime;

		currentTime = newTime;

		accumulator += frameTime;

		SDL_Event event;
		SDL_PollEvent(&event);
		if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.scancode) {
			case SDL_SCANCODE_Q:
				break;
			case SDL_SCANCODE_W:
				PAccel.y = -1;
				break;

			case SDL_SCANCODE_S:
				PAccel.y = 1;
				break;

			case SDL_SCANCODE_A:
				PAccel.x = -1;
				break;

			case SDL_SCANCODE_D:
				PAccel.x = 1;
				break;

			default:
				break;
			}
		}

		if (event.type == SDL_KEYUP) {
			switch (event.key.keysym.scancode) {
			case SDL_SCANCODE_Q:
				break;
			case SDL_SCANCODE_W:
				PAccel.y = 0;
				break;

			case SDL_SCANCODE_S:
				PAccel.y = 0;
				break;

			case SDL_SCANCODE_A:
				PAccel.x = 0;
				break;

			case SDL_SCANCODE_D:
				PAccel.x = 0;
				break;
			default:
				break;
			}
		}
		//william.UpdatePos(GM->PControls());
		william.UpdatePos(Vector2f(PAccel.x, PAccel.y));

		while (accumulator >= timeStep)
		{
			// Get our controls and events
			while (SDL_PollEvent(&event))
			{
				if (event.type == SDL_QUIT)
					gameRunning = false;
			}
			accumulator -= timeStep;
		}

		const float alpha = accumulator / timeStep; //50%

		window.clear();
		window.renderBack(Background);
		

		for (Actor& e : entitiees)
		{
			window.renderAct(e);
		}
		//william.UpdatePos(Vector2f(PAccel.x, PAccel.y));
		enemy.UpdatePos(Vector2f(EAceel.x, EAceel.y));
		//std::cout << william.getPos().x << std::endl;
		//enemy moves by y
		if (enemy.getPos().x > 100) {
			EAceel.set(-0.3,0.0);
		}
		else if (enemy.getPos().x < 40) {
			EAceel.set(0.3,0.0);
		}

		/*if (william.getPos().x > 320) {
			PAccel.set(-0.5, 0);
		}
		else if (william.getPos().x < 50) {
			PAccel.set(0.5, 0);
		}*/

		//calculate distance
		float x = william.getPos().x + 30 - enemy.getPos().x;
		float y = william.getPos().y - enemy.getPos().y;
		float hyp = sqrt(x * x + y * y); // distance
		x /= hyp;
		y /= hyp;

		
		if (hyp > 30 && hyp < 100) {
				
			//std::cout << "move enemy" << std::endl;
			enemy.UpdatePos(Vector2f(x, y));
		}

		
		window.renderAct(william);
		window.renderAct(enemy);
		window.display();

		int frameTicks = SDL_GetTicks() - startTicks;

		if (frameTicks < 1000 / window.getRefreshRate())
			SDL_Delay(1000 / window.getRefreshRate() - frameTicks);
		
	}

	window.cleanUp();
	SDL_Quit();

	return 0;
}