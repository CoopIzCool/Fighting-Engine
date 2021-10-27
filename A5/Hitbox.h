#pragma once
#include "Entity.h"
class Hitbox
{
public:
	Hitbox(Entity* et, int dam, DirectX::XMFLOAT3 launch, int start, int active, int end);
	~Hitbox();
	Entity* GetEntity();
	int Damage();
	DirectX::XMFLOAT3 Launch();
	DirectX::XMFLOAT3 P2Launch();
	int Start(); 
	int Active();
	int End();
private:
	Entity* entity;
	int damage;
	DirectX::XMFLOAT3 launchVector;
	int startFrames;
	int activeFrames;
	int endFrames;
};

