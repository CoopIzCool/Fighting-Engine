#include "Player.h"
#include <iostream>

Player::Player(Entity* et, int hitP, bool p2)
{
	entity = et;
	hitpoints = hitP;
	isP2 = p2;
}

Player::~Player()
{
}

void Player::Update(float dt)
{
	if (alive)
	{
		float speed = dt * 3.0f;
		Transform tf = *entity->GetTransform();
		//directions for p1
		if (!isP2)
		{


			if (GetAsyncKeyState('W') & 0x8000 && (!freeFall))
			{
				entity->GetTransform()->MoveRelative(0, speed, 0);
				if (jumpFrames == 0)
				{
					jumpPressed = true;
				}
				jumpFrames+= (dt * 60.0f);
				std::cout << jumpFrames<< std::endl;
				
			}
			else if (tf.getPosition().y > 0)
			{
				entity->GetTransform()->MoveRelative(0, -speed, 0);
			}
			else
			{
				entity->GetTransform()->setPosition(tf.getPosition().x, 0, tf.getPosition().z);
				freeFall = false;
				jumpFrames = 0.0f;
				jumpPressed = false;
			}

			if (GetAsyncKeyState('A') & 0x8000)
			{
				entity->GetTransform()->MoveRelative(-speed, 0, 0);
				//wall collision
				if (entity->GetTransform()->getPosition().x < -1.2f)
				{
					entity->GetTransform()->setPosition(-1.2f, tf.getPosition().y, tf.getPosition().z);
				}
			}
			if (GetAsyncKeyState('D') & 0x8000)
			{
				entity->GetTransform()->MoveRelative(speed, 0, 0);
				//wall collision
				if (entity->GetTransform()->getPosition().x > 1.35f)
				{
					entity->GetTransform()->setPosition(1.38f, tf.getPosition().y, tf.getPosition().z);
				}
			}
			//turns off the abillity tojump after the player has jumped for a period of time or if the jump button is let go
			if (!freeFall && !GetAsyncKeyState('W') && jumpPressed)
			{
				freeFall = true;
				jumpFrames = 0.0f;
			}
			if (!freeFall && jumpFrames >= 10.0f)
			{
				freeFall = true;
				jumpFrames = 0.0f;
			}


		}
		//for p2
		else
		{
			if (GetAsyncKeyState('I') & 0x8000 && (!freeFall))
			{
				entity->GetTransform()->MoveRelative(0, speed, 0);
				if (jumpFrames == 0.0f)
				{
					jumpPressed = true;
				}
				jumpFrames += (dt * 60.0f);
			}
			else if (tf.getPosition().y > 0)
			{
				entity->GetTransform()->MoveRelative(0, -speed, 0);
			}
			else
			{
				entity->GetTransform()->setPosition(tf.getPosition().x, 0, tf.getPosition().z);
				freeFall = false;
				jumpFrames = 0.0f;
				jumpPressed = false;
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
			//jumping logic for p2
			if (!freeFall && !GetAsyncKeyState('I') && jumpPressed)
			{
				freeFall = true;
				jumpFrames = 0.0f;
			}
			if (!freeFall && jumpFrames >= 10.0f)
			{
				freeFall = true;
				jumpFrames = 0.0f;
			}
		}
	}
}

void Player::Damage(int dmg)
{
	if (alive)
	{
		hitpoints -= dmg;
		if (hitpoints <= 0)
		{
			hitpoints = 0;
			alive = false;
		}
	}
}

Entity* Player::GetEntity()
{
	return entity;
}

int Player::GetHealth()
{
	return hitpoints;
}

bool Player::isGrounded()
{
	return (!freeFall & !jumpPressed);
}

float Player::GetStart()
{
	return frames[0];
}

float Player::GetActive()
{
	return frames[1];
}

float Player::GetEnd()
{
	return frames[2];
}

void Player::SetFrames(Hitbox* hb)
{
	frames[0] = hb->Start();
	frames[1] = hb->Active();
	frames[2] = hb->End();
	ActiveHitbox = hb;
}

void Player::ResetFrames()
{
	frames[0] = 0;
	frames[1] = 0;
	frames[2] = 0;
}

