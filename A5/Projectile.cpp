#include "Player.h"

using namespace ::DirectX;
Projectile::Projectile(Entity* et, int dam,float p1X, float p2X,float height, bool owner)
{
	entity = et;
	damage = dam;
	Shot(p1X,p2X,height);
	isP1Owner = owner;
}

Projectile::~Projectile()
{
}

void Projectile::Shot(float p1X, float p2X, float height)
{ 
	//determines the direction in which the projectile should be fired based on character's x positions
	float direction = p1X - p2X;
	if (direction > 0)
	{
		isRight = false;
		entity->GetTransform()->setPosition(p1X - 0.15f, height, 0.0f);
	}
	else
	{
		isRight = true;
		entity->GetTransform()->setPosition(p1X + 0.15f, height, 0.0f);
	}
}

void Projectile::Update(float dt)
{
	if (isRight)
	{
		entity->GetTransform()->MoveRelative(dt/12.0f, 0.0f, 0.0f);
		if (entity->GetTransform()->getPosition().x > 15.0f)
		{
			active = false;
		}
	}
	else
	{
		entity->GetTransform()->MoveRelative(dt * -1.0f/12.0f, 0.0f, 0.0f);
		if (entity->GetTransform()->getPosition().x < -15.0f)
		{
			active = false;
		}
	}
}

bool Projectile::isColliding(Entity* playerEt)
{
	//adjust min and max bounds with the players position
	XMVECTOR playMin = XMVectorAdd(XMLoadFloat3(&playerEt->GetMesh()->GetMinBounds()), XMLoadFloat3(&playerEt->GetTransform()->getPosition()));
	XMVECTOR playMax = XMVectorAdd(XMLoadFloat3(&playerEt->GetMesh()->GetMaxBounds()), XMLoadFloat3(&playerEt->GetTransform()->getPosition()));
	XMVECTOR thisMin = XMVectorAdd(XMLoadFloat3(&entity->GetMesh()->GetMinBounds()), XMLoadFloat3(&entity->GetTransform()->getPosition()));
	XMVECTOR thisMax = XMVectorAdd(XMLoadFloat3(&entity->GetMesh()->GetMaxBounds()), XMLoadFloat3(&entity->GetTransform()->getPosition()));
	XMFLOAT3 minPlayer;
	XMFLOAT3 maxPlayer;
	XMFLOAT3 minProj;
	XMFLOAT3 maxProj;

	XMStoreFloat3(&minPlayer, playMin);
	XMStoreFloat3(&maxPlayer, playMax);
	XMStoreFloat3(&minProj, thisMin);
	XMStoreFloat3(&maxProj, thisMax);
	//compare the bounds and see if they interesect
	if (minPlayer.x <= maxProj.x && maxPlayer.x >= minProj.x &&
		minPlayer.y <= maxProj.y && maxPlayer.y >= minProj.y)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int Projectile::GetDamage()
{
	return damage;
}

bool Projectile::GetActive()
{
	return active;
}

Entity* Projectile::GetEntity()
{
	return entity;
}

bool Projectile::GetOwner()
{
	return isP1Owner;
}

void Projectile::SetActive(bool a)
{
	active = a;
}


