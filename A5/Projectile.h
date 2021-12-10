#pragma once
#include "Entity.h"
#include "Player.h"
#include <DirectXMath.h>
class Projectile
{
public:
	Projectile(Entity* et, int dam, float p1X,float p2X, float height, bool owner);
	Projectile(Entity* et, int dam);
	~Projectile();
	void Shot(float p1X, float p2X,float height);
	bool Update(float dt);
	bool isColliding(Entity* playerEt);
	int GetDamage();
	bool GetActive();
	Entity* GetEntity();
	bool GetOwner();
	void SetActive(bool a);
	void SetOwner(bool o);
	
private:
	Entity* entity;
	int damage;
	bool isRight = true;
	bool active = true;
	bool isP1Owner;
};

