#pragma once
#include "Entity.h"
#include "Mesh.h"
#include "Material.h"

class Player
{
public:
	Player(Entity* et, bool p2);
	Player(Entity* et, int hitP, bool p2, Vertex* verts);
	~Player();
	void Update(float dt);
	void Damage(int dmg);
	Entity* GetEntity();
	void GetBounds(Vertex* verts);
private:
	Entity* entity;
	int hitpoints = 100;
	bool isP2;
	DirectX::XMFLOAT3 minBounds = DirectX::XMFLOAT3(FLT_MIN, FLT_MIN, FLT_MIN);
	DirectX::XMFLOAT3 maxBounds = DirectX::XMFLOAT3(FLT_MAX, FLT_MAX, FLT_MAX);
};

