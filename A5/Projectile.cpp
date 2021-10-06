#include "Projectile.h"

Projectile::Projectile(Entity* et, int dam,float p1X, float p2X,float height)
{
	entity = et;
	damage = dam;
	Shot(p1X,p2X,height);
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
