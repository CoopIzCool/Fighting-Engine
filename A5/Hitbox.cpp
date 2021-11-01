#include "Hitbox.h"

Hitbox::Hitbox(Entity* et, int dam, DirectX::XMFLOAT3 launch, float start, float active, float end)
{
	entity = et;
	damage = dam;
	launchVector = launch;
	startFrames = start;
	activeFrames = active;
	endFrames = end;
}

Hitbox::~Hitbox()
{
}

Entity* Hitbox::GetEntity()
{
	return entity;
}

int Hitbox::Damage()
{
	return damage;
}

DirectX::XMFLOAT3 Hitbox::Launch()
{
	return launchVector;
}

DirectX::XMFLOAT3 Hitbox::P2Launch()
{
	//inverts the x component of the launch vector
	float invertedX = launchVector.x * -1.0f;
	return DirectX::XMFLOAT3(invertedX,launchVector.y,launchVector.z);
}

float Hitbox::Start()
{
	return startFrames;
}

float Hitbox::Active()
{
	return activeFrames;
}

float Hitbox::End()
{
	return endFrames;
}
