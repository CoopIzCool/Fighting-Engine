#include "Player.h"


Player::Player(Entity* et)
{
}

Player::Player(Entity* et, int hitP)
{
	entity = et;
	hitpoints = hitP;
}

Player::~Player()
{
}

void Player::Update(float dt)
{
	float speed = dt * 3.0f;
	Transform tf = *entity->GetTransform();
	//directions
	if (GetAsyncKeyState('W') & 0x8000)
	{
		entity->GetTransform()->MoveRelative(0, speed, 0);
	}
	else if (tf.getPosition().y > 0)
	{
		entity->GetTransform()->MoveRelative(0, -speed, 0);
	}
	else
	{
		entity->GetTransform()->setPosition(tf.getPosition().x, 0, tf.getPosition().z);
	}

	if (GetAsyncKeyState('A') & 0x8000)
	{
		entity->GetTransform()->MoveRelative(-speed, 0, 0);
	}
	if (GetAsyncKeyState('D') & 0x8000)
	{
		entity->GetTransform()->MoveRelative(speed, 0, 0);
	}

}

void Player::Damage(int dmg)
{

}

Entity* Player::GetEntity()
{
	return entity;
}
