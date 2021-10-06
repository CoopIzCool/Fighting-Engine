#pragma once
#include "Entity.h"
#include "Player.h"
class Projectile
{
public:
	Projectile(Entity* et, int dam, float p1X,float p2X, float height, bool owner);
	~Projectile();
	void Shot(float p1X, float p2X,float height);
	void Update(float dt);
	int GetDamage();
	bool GetActive();
	Entity* GetEntity();
	bool GetOwner();
	void SetActive(bool a);
	bool isColliding(Player* player);
private:
	Entity* entity;
	int damage;
	bool isRight = true;
	bool active = true;
	bool isP1Owner;
};

