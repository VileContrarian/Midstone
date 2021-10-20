#ifndef CHARACTERSPAWN_H
#define CHARACTERSPAWN_H
#include "Vector.h"
using namespace MATH;

/*The CharacterSpawn Class will be used to create spawn points for the player and enemies, 
based on whether or not they have reached a checkpoint.*/
class CharacterSpawn
{
private:
	//playerIsDead will check to see if the player's health is less than or equal to 0, returning the player to their last spawn point/checkpoint.
	bool playerIsDead;
	//location vec3 will represent the location of the actual spawn, as well as player's respawn location for checkpoints
	Vec3 location;
	//This boolean will throw true if the player has managed to reach a checkpoint, setting the player's new spawn to that location.
	bool checkpointWasReached;
public:
	CharacterSpawn(Vec3 location);
	~CharacterSpawn();
	bool OnCreate();
	void OnDestroy();
	void Update(const float time);
};
#endif
