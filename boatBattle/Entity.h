#pragma once

#include <DirectXMath.h>
#include "Transform.h"
#include "Mesh.h"
#include "Material.h"
class Entity
{
public:

	Entity(Mesh* me,Material* ma);
	~Entity();

	Mesh* GetMesh();
	Transform* GetTransform();
	Material* GetMaterial();

private:
	Transform transform;
	Mesh* mesh;
	Material* material;
	
};

