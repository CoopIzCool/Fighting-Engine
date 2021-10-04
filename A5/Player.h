#pragma once
#include "Entity.h"
#include "Mesh.h"
#include "Material.h"

class Player
{
public:
	Player(Entity* et, bool p2);
	Player(Entity* et, int hitP, bool p2);
	~Player();
	void Update(float dt);
	void Damage(int dmg);
	Entity* GetEntity();
private:
	Entity* entity;
	int hitpoints = 100;
	bool isP2;
};

