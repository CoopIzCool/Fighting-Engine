#pragma once
#include "Entity.h"
class Projectile
{
public:
	Projectile(Entity* et, int dam, float p1X,float p2X, float height);
	~Projectile();
	void Shot(float p1X, float p2X,float height);
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

