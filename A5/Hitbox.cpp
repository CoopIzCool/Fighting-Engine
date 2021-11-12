#include "Hitbox.h"



Hitbox::Hitbox(Entity* et, int dam, DirectX::XMFLOAT3 launch, float start, float active, float end,hitboxes HBtype)
{
	entity = et;
	damage = dam;
	launchVector = launch;
	startFrames = start;
	activeFrames = active;
	endFrames = end;
	type = HBtype;
}

Hitbox::~Hitbox()
{
}

void Hitbox::SetTransform(float p1X, float p2X, float height)
{
	
	//determines the direction in which the projectile should be fired based on character's x positions
	float direction = p1X - p2X;
	if (direction > 0)
	{
		//isRight = false;
		entity->GetTransform()->setPosition(p1X - 0.15f, height, 0.0f);
	}
	else
	{
		//isRight = true;
		entity->GetTransform()->setPosition(p1X + 0.15f, height, 0.0f);
	}
	
}

bool Hitbox::isColliding(Entity* playerEt)
{
	DirectX::XMFLOAT3 priorPlayerMin = playerEt->GetMesh()->GetMinBounds();
	DirectX::XMFLOAT3 priorPlayerMax = playerEt->GetMesh()->GetMaxBounds();
	DirectX::XMFLOAT3 priorEntMin = entity->GetMesh()->GetMinBounds();
	DirectX::XMFLOAT3 priorEntMax = entity->GetMesh()->GetMaxBounds();
	DirectX::XMFLOAT3 playerPos = playerEt->GetTransform()->getPosition();
	DirectX::XMFLOAT3 etPos = entity->GetTransform()->getPosition();
	//adjust min and max bounds with the players position
	DirectX::XMVECTOR playMin = DirectX::XMVectorAdd(XMLoadFloat3(&priorPlayerMin), XMLoadFloat3(&playerPos));
	DirectX::XMVECTOR playMax = DirectX::XMVectorAdd(XMLoadFloat3(&priorPlayerMax), XMLoadFloat3(&playerPos));
	DirectX::XMVECTOR thisMin = DirectX::XMVectorAdd(XMLoadFloat3(&priorEntMin), XMLoadFloat3(&etPos));
	DirectX::XMVECTOR thisMax = DirectX::XMVectorAdd(XMLoadFloat3(&priorEntMax), XMLoadFloat3(&etPos));
	DirectX::XMFLOAT3 minPlayer;
	DirectX::XMFLOAT3 maxPlayer;
	DirectX::XMFLOAT3 minProj;
	DirectX::XMFLOAT3 maxProj;
	
	DirectX::XMStoreFloat3(&minPlayer, playMin);
	DirectX::XMStoreFloat3(&maxPlayer, playMax);
	DirectX::XMStoreFloat3(&minProj, thisMin);
	DirectX::XMStoreFloat3(&maxProj, thisMax);
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

Entity* Hitbox::GetEntity()
{
	return entity;
}

int Hitbox::GetDamage()
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

bool Hitbox::VisibleHitbox()
{
	return showHitBox;
}

hitboxes Hitbox::Type()
{
	return type;
}


