#pragma once
#include <DirectXMath.h>
#include "Transform.h"
#include "Mesh.h"
#include "Material.h"
#include "Cannonball.h"
#include "Entity.h"
class Enemy
{
public:

	Enemy(Mesh* me, Material* ma, DirectX::XMFLOAT3 direction);
	~Enemy();

	Mesh* GetMesh();
	Transform* GetTransform();
	Material* GetMaterial();
	bool isActive();
	void setInactive();
	void Update(float dt);
	void setDirection();
	bool isColliding(Cannonball* obj);
	bool isColliding(Entity* obj);

private:
	Transform transform;
	Mesh* mesh;
	Material* material;
	DirectX::XMFLOAT3 Direction;
	bool active = true;
};

