#pragma once
#include "Entity.h"
#include "Mesh.h"
#include "Material.h"
#include "Projectile.h"
#include "Hitbox.h"

class Player
{
public:
	Player(Entity* et, int hitP, bool p2);
	~Player();
	void Update(float dt);
	void Damage(int dmg);
	Entity* GetEntity();
	int GetHealth();
	bool isGrounded();
	float GetStart();
	float GetActive();
	float GetEnd();
	void SetFrames(Hitbox* hb);
	void ResetFrames();
	
private:
	Entity* entity;
	int hitpoints = 100;
	bool isP2;
	bool alive = true;
	float jumpFrames = 0;
	bool freeFall = false;
	bool jumpPressed = false;
	float frames[3] = { 0,0,0 };
	Hitbox* ActiveHitbox = nullptr;
};

