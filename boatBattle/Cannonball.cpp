#include "Cannonball.h"

Cannonball::Cannonball(Mesh* me, Material* ma)
{
	mesh = me;
	material = ma;
}

Cannonball::~Cannonball()
{
}

Mesh* Cannonball::GetMesh()
{
	return mesh;
}

Transform* Cannonball::GetTransform()
{
	return &transform;
}

Material* Cannonball::GetMaterial()
{
	return material;
}

bool Cannonball::isActive()
{
	return active;
}

void Cannonball::setInactive()
{
	active = false;
}

void Cannonball::Update(float dt)
{
	float speed = 1.5f * dt;
	transform.MoveRelative(0,0,speed);
}
