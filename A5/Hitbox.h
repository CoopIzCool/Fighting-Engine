#pragma once
#include "Entity.h"

class Hitbox
{
public:
	Hitbox(Entity* et, int dam, DirectX::XMFLOAT3 launch, float start, float active, float end);
	~Hitbox();
	void SetTransform(float p1X, float p2X, float height);
	bool isColliding(Entity* playerEt);
	Entity* GetEntity();
	int GetDamage();
	DirectX::XMFLOAT3 Launch();
	DirectX::XMFLOAT3 P2Launch();
	float Start(); 
	float Active();
	float End();
	bool VisibleHitbox();
	
private:
	Entity* entity;
	int damage;
	DirectX::XMFLOAT3 launchVector;
	float startFrames;
	float activeFrames;
	float endFrames;
	bool showHitBox = true;
};

