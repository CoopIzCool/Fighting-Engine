#pragma once
#include "Entity.h"
class Projectile
{
private:
	Projectile(Entity* et, int dam,int direction);
	~Projectile();
	void Shot(int direction);
	void Update(float dt);
	int GetDamage();
public:
	Entity* entity;
	int damage;
	bool isRight = true;
};

