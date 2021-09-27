#pragma once

#include <DirectXMath.h>
#include "Transform.h"
#include "Mesh.h"
#include "Material.h"

class Cannonball
{
public:

	Cannonball(Mesh* me, Material* ma);
	~Cannonball();

	Mesh* GetMesh();
	Transform* GetTransform();
	Material* GetMaterial();
	bool isActive();
	void setInactive();
	void Update(float dt);

private:
	Transform transform;
	Mesh* mesh;
	Material* material;
	DirectX::XMFLOAT3 firedDirection;
	bool active = true;
};

