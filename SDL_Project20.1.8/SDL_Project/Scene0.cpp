#include "Scene0.h"
#include <SDL.h>
#include <SDL_image.h>
#include "Randomizer.h"
#include <iostream>

Scene0::Scene0(SDL_Window* sdlWindow_){
	window = sdlWindow_;
	background = new Body(Vec3(0.0f, 15.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), 0.0f);
}

Scene0::~Scene0(){
	delete background;
}

bool Scene0::OnCreate() {
	int w, h;
	float xAxis = 30.0f;
	float yAxis = 15.0f;
	SDL_GetWindowSize(window,&w,&h);
	
	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(0.0f, xAxis, 0.0f, yAxis, 0.0f, 1.0f);
	projectionMatrix = ndc * ortho;
	
	IMG_Init(IMG_INIT_PNG);
	SDL_Surface* backgroundImage = IMG_Load("Test.png");
	if(backgroundImage == nullptr){
		std::cerr << "Can't open the image" << std::endl;
		return false;
	} else {
		background->setImage(backgroundImage);
		Vec3 worldCoordsFromScreenCoords;
		worldCoordsFromScreenCoords.x = xAxis / static_cast<float>(w) * static_cast<float>(backgroundImage->w);
		worldCoordsFromScreenCoords.y = yAxis / static_cast<float>(h) * static_cast<float>(backgroundImage->h);
		background->setImageSizeWorldCoords(worldCoordsFromScreenCoords);
		
	}
	return true;
}

void Scene0::OnDestroy() {

}

void Scene0::Update(const float deltaTime) {

}


void Scene0::HandleEvents(const SDL_Event& sdlEvent){
	
}


void Scene0::Render() {

	SDL_Rect square;
	Vec3 screenCoords;
	SDL_Surface* screenSurface = SDL_GetWindowSurface(window);
	SDL_FillRect(screenSurface, nullptr, SDL_MapRGB(screenSurface->format, 0, 0, 0));

	screenCoords = projectionMatrix * background->getPos();
	square.x = static_cast<int>(screenCoords.x);
	square.y = static_cast<int>(screenCoords.y);
	square.w = background->getImage()->w ;
	square.h = background->getImage()->h;
	SDL_BlitSurface(background->getImage(), nullptr, screenSurface, &square);
	//SDL_RenderCopyEx(renderer, background->getTexture(), nullptr, &square, background->getRotation(), nullptr, SDL_FLIP_NONE);

	SDL_UpdateWindowSurface(window);
}