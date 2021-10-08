#ifndef CHARACTERSPAWN_H
#define CHARACTERSPAWN_H
#include "Vector.h"

/*The CharacterSpawn Class will be used to create spawn points for the player and enemies, 
based on whether or not they have reached a checkpoint.*/
class CharacterSpawn
{
private:
	//playerIsDead will check to see if the player's health is less than or equal to 0, returning the player to their last spawn point/checkpoint.
	bool playerIsDead;

public:
	CharacterSpawn();
	~CharacterSpawn();
	bool OnCreate();
	void OnDestroy();
	void Update(const float time);
};
#endif
