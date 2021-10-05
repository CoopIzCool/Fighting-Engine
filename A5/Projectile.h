#pragma once
#include "Entity.h"
class Projectile
{
public:
	Projectile(Entity* et, int dam,int direction);
	~Projectile();
	void Shot(int direction);
	void Update(float dt);
	int GetDamage();
	bool GetActive();
	Entity* GetEntity();
private:
	Entity* entity;
	int damage;
	bool isRight = true;
	bool active = true;
};

