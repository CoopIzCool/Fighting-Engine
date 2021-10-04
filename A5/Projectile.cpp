#include "Projectile.h"

Projectile::Projectile(Entity* et, int dam,int direction)
{
	entity = et;
	damage = dam;
	Shot(direction);
}

Projectile::~Projectile()
{
}

void Projectile::Shot(int direction)
{ 
	//determines the direction in which the projectile should be fired based on character's x positions
	if (direction > 0)
	{
		isRight = false;
	}
	else
	{
		isRight = true;
	}
}

void Projectile::Update(float dt)
{
	if (isRight)
	{
		entity->GetTransform()->MoveRelative(dt, 0.0f, 0.0f);
	}
	else
	{
		entity->GetTransform()->MoveRelative(dt * -1.0f, 0.0f, 0.0f);
	}
}

int Projectile::GetDamage()
{
	return damage;
}
