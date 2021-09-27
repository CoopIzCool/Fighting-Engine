#include "Entity.h"
#include "Vertex.h"
#include "Mesh.h"
#include "Transform.h"
#include "DXCore.h"
#include <DirectXMath.h>

using namespace DirectX;
Entity::Entity(Mesh* me, Material* ma)
{
	mesh = me;
	material = ma;
}

Entity::~Entity()
{
}

Mesh* Entity::GetMesh()
{
	return mesh;
}

Transform* Entity::GetTransform()
{
	return &transform;
}

Material* Entity::GetMaterial()
{
	return material;
}




