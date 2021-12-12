#include"Player.h"

Actor::Actor(Vector2f p_pos, float mass_, SDL_Texture* p_tex)
	:pos(p_pos), tex(p_tex)
{
	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = 32;
	currentFrame.h = 42;

}

void Player::Update() {

}
