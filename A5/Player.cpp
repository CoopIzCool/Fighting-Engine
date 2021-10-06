#include "Player.h"
#include <iostream>


Player::Player(Entity* et, bool p2)
{
}

Player::Player(Entity* et, int hitP, bool p2, Vertex* verts)
{
	entity = et;
	hitpoints = hitP;
	isP2 = p2;
	//GetBounds(verts);
}

Player::~Player()
{
}

void Player::Update(float dt)
{
	float speed = dt * 3.0f;
	Transform tf = *entity->GetTransform();
	//directions for p1
	if (!isP2)
	{
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
			if (entity->GetTransform()->getPosition().x < -1.2f)
			{
				entity->GetTransform()->setPosition(-1.2f, tf.getPosition().y, tf.getPosition().z);
			}
		}
		if (GetAsyncKeyState('D') & 0x8000)
		{
			entity->GetTransform()->MoveRelative(speed, 0, 0);
			if (entity->GetTransform()->getPosition().x > 1.35f)
			{
				entity->GetTransform()->setPosition(1.38f, tf.getPosition().y, tf.getPosition().z);
			}
		}
		if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		{
			std::cout << entity->GetTransform()->getPosition().x;
		}
	}
	//for p2
	else
	{
		if (GetAsyncKeyState('I') & 0x8000)
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

		if (GetAsyncKeyState('J') & 0x8000)
		{
			entity->GetTransform()->MoveRelative(-speed, 0, 0);
			if (entity->GetTransform()->getPosition().x < -1.5f)
			{
				entity->GetTransform()->setPosition(-1.5f, tf.getPosition().y, tf.getPosition().z);

			}
		}
		if (GetAsyncKeyState('L') & 0x8000)
		{
			entity->GetTransform()->MoveRelative(speed, 0, 0);
			if (entity->GetTransform()->getPosition().x > 1.08f)
			{
				entity->GetTransform()->setPosition(1.08f, tf.getPosition().y, tf.getPosition().z);
			}
		}
	}

}

void Player::Damage(int dmg)
{

}

Entity* Player::GetEntity()
{
	return entity;
}

void Player::GetBounds(Vertex* verts)
{
	for (int i = 0; i < 4; i++)
	{
		if (verts[i].Position.x > maxBounds.x)
		{
			maxBounds.x = verts[i].Position.x;
		}
		else if (verts[i].Position.x < minBounds.x)
		{
			minBounds.x = verts[i].Position.x;
		}
		if (verts[i].Position.y > maxBounds.y)
		{
			maxBounds.y = verts[i].Position.y;
		}
		else if (verts[i].Position.y < minBounds.y)
		{
			minBounds.y = verts[i].Position.y;
		}
		if (verts[i].Position.z > maxBounds.z)
		{
			maxBounds.z = verts[i].Position.z;
		}
		else if (verts[i].Position.z < minBounds.z)
		{
			minBounds.z = verts[i].Position.z;
		}
	}
}
