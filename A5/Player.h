#pragma once
#include "Entity.h"
#include "Mesh.h"
#include "Material.h"

class Player: Entity
{
public:
	Player() :Entity(Mesh* me, Material* ma);
	void Update(float dt);
	void Damage(int dmg);
private:
	int hitpoints = 100;
};

