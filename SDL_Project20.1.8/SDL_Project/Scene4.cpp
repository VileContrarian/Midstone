#include "Scene4.h"
#include <SDL.h>
#include <SDL_image.h>
#include "Randomizer.h"
#include <iostream>
#include "VMath.h"
using namespace MATH;

Scene4::Scene4(SDL_Window* sdlWindow_){
	Randomizer r;
	window = sdlWindow_;
	renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
	
		//Make first element the plant
		gameObjects[0] = new Ball(Vec3(10.0f, 20.0f, 0.0f),
							    Vec3(-5.0f, 1.0f, 0.0f), 
								Vec3(0.0f, 0.0f, 0.0f), 1.0f);

		// star 1
		gameObjects[1] = new Ball(Vec3(5.0f, 10.0f, 0.0f),
								Vec3(0.0, 0.0f, 0.0f),
								Vec3(0.0f, 0.0f, 0.0f), 100.0f);
		// star 2
		gameObjects[2] = new Ball(Vec3(15.0f, 25.0f, 0.0f),
								Vec3(0.0, 0.0f, 0.0f),
								Vec3(0.0f, 0.0f, 0.0f), 150.0f);
	
}

Scene4::~Scene4(){
	for(int i = 0; i < NUM_OBJECTS; ++i){
		delete gameObjects[i];
	}
	SDL_DestroyRenderer(renderer);
}

bool Scene4::OnCreate() {
	int w, h;
	float xAxis = 25.0f;
	float yAxis = 40.0f;
	SDL_GetWindowSize(window,&w,&h);
	
	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(-20, 35, -20, 40, 0.0f, 1.0f);
	projectionMatrix = ndc * ortho;
	invProjectionMatrix = MMath::inverse(projectionMatrix);
	
	IMG_Init(IMG_INIT_PNG);
	SDL_Surface* ballImage = IMG_Load("ball.png");
	SDL_Texture* ballTexture = SDL_CreateTextureFromSurface(renderer,ballImage);
	if(ballTexture == nullptr) printf("%s\n",SDL_GetError());
	if(ballImage == nullptr){
		std::cerr << "Can't open the image" << std::endl;
		return false;
	} else {
		
		/// Do some tricks with the image coords
		Vec3 upperLeft(0.0f,0.0f,0.0f); 
		Vec3 lowerRight(static_cast<float>(ballImage->w), static_cast<float>(ballImage->h),0.0f);
		Vec3 ulWorld = invProjectionMatrix * upperLeft;
		Vec3 lrWorld = invProjectionMatrix * lowerRight;
		Vec3 worldCoordsFromScreenCoords = lrWorld - ulWorld;
		///float r = worldCoordsFromScreenCoords.x / 2.0f;
		
		for(int i = 0; i < NUM_OBJECTS; i++){
			gameObjects[i]->setTexture(ballTexture);
			gameObjects[i]->setImageSizeWorldCoords(worldCoordsFromScreenCoords);
		}
		SDL_FreeSurface(ballImage);	
	}
	return true;
}

void Scene4::OnDestroy() {
	/// We really need to deal with the textures better, they are left dangling right now
	SDL_DestroyRenderer(renderer);
}

void Scene4::Update(const float deltaTime) {
	//Applyforce to plant using number from part 1 of assigment
	//Applyforce to planet
	//Vec3 netForce(1.7635f, 1.4058f, 0.0f);
	// dont hard code the numbers for the force of gravity
	// look at the formulas in the update secton
	// and maybe create variables for the values that are used more than once
	//gameObjects[0]->ApplyForce(netForce);

	Vec3 PS1 = gameObjects[1]->getPos() - gameObjects[0]->getPos();
	float distance1 = sqrt((PS1.x * PS1.x) + (PS1.y * PS1.y));
	float distance1square = distance1 * distance1;
	float Fg1 = (1 * 100 * 1) / distance1square;
	float Norm1x = PS1.x / distance1;
	float Norm1y = PS1.y / distance1;
	float force1x = Fg1 * Norm1x;
	float force1y = Fg1 * Norm1y;

	Vec3 PS2 = gameObjects[2]->getPos() - gameObjects[0]->getPos();
	float distance2 = sqrt((PS2.x * PS2.x) + (PS2.y * PS2.y));
	float distance2square = distance2 * distance2;
	float Fg2 = (1 * 150 * 1) / distance2square;
	float Norm2x = PS2.x / distance2;
	float Norm2y = PS2.y / distance2;
	float force2x = Fg2 * Norm2x;
	float force2y = Fg2 * Norm2y;

	float Nforcex = (force2x) + (force1x);
	float Nforcey = (force2y)+(force1y);

	Vec3 Nforce (force1x + force2x, force1y + force2y, 0.0f) ;

	gameObjects[0]->ApplyForce(Nforce);


	//Just update planet
	gameObjects[0]->Update(deltaTime);
	gameObjects[1]->Update(deltaTime);
	gameObjects[2]->Update(deltaTime);
}



void Scene4::HandleEvents(const SDL_Event& sdlEvent){
	if (sdlEvent.type == SDL_MOUSEBUTTONDOWN && sdlEvent.button.button == SDL_BUTTON_LEFT) {
		Vec3 mouseCoords(static_cast<float>(sdlEvent.button.x), static_cast<float>(sdlEvent.button.y),0.0f);
		Vec3 worldCoords = invProjectionMatrix * mouseCoords;
		worldCoords.z = 0.0f;
		for (int i = 0; i < NUM_OBJECTS; ++i) {
			Vec3 pos = gameObjects[i]->getPos();
			float distance = VMath::distance(pos , worldCoords);
			float radius = gameObjects[i]->getRadius();
			if(distance < radius){
				printf("Gotcha ball %d\n",i);
			}
		}
	}
}


void Scene4::Render() {
	SDL_SetRenderDrawColor(renderer, 0,0,0,0);
	SDL_RenderClear(renderer);
	SDL_Rect square;
	Vec3 screenCoords;
	int w,h;
	
	for(int i = 0; i < NUM_OBJECTS; ++i){
		SDL_QueryTexture(gameObjects[i]->getTexture(), nullptr, nullptr, &w, &h);
		screenCoords = projectionMatrix * gameObjects[i]->getPos();
		square.x = static_cast<int>(screenCoords.x) - w/2;
		square.y = static_cast<int>(screenCoords.y) - h/2;
		square.w = w;
		square.h = h;
		SDL_RenderCopyEx(renderer, gameObjects[i]->getTexture(),nullptr, &square, gameObjects[i]->getRotation(), nullptr, SDL_FLIP_NONE);
		
	}
	SDL_RenderPresent(renderer);
}