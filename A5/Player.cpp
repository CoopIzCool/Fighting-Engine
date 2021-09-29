#include "Player.h"

void Player::Update(float dt)
{
	float speed = dt * 3.0f;

	//directions
	if (GetAsyncKeyState('W') & 0x8000)
	{
		transform.MoveRelative(0, speed,0);
	}
	else if (transform.getPosition().y > 0)
	{
		transform.MoveRelative(0, -speed, 0);
	}
	else
	{
		transform.setPosition(transform.getPosition().x, 0, transform.getPosition().z);
	}

	if (GetAsyncKeyState('A') & 0x8000)
	{
		transform.MoveRelative(-speed, 0, 0);
	}
	if (GetAsyncKeyState('D') & 0x8000)
	{
		transform.MoveRelative(speed, 0, 0);
	}

}

void Player::Damage(int dmg)
{
}
