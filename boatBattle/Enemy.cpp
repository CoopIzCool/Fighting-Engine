#include "Enemy.h"

using namespace DirectX;
Enemy::Enemy(Mesh* me, Material* ma, DirectX::XMFLOAT3 direction)
{
	mesh = me;
	material = ma;
	Direction = direction;
}

Enemy::~Enemy()
{
}

Mesh* Enemy::GetMesh()
{
	return mesh;
}

Transform* Enemy::GetTransform()
{
	return &transform;
}

Material* Enemy::GetMaterial()
{
	return material;
}

bool Enemy::isActive()
{
	return active;
}

void Enemy::setInactive()
{
	active = false;
}

void Enemy::Update(float dt)
{

	transform.MoveAbsolute(Direction.x, 0, Direction.z);
}

void Enemy::setDirection() {
	//find the direction the point is moving and set its direction moving to it to allow for easy moving
	XMFLOAT3 storage;
	XMStoreFloat3(&storage, XMVectorSubtract(XMLoadFloat3(&transform.getPosition()), XMLoadFloat3(&Direction)));
	
	storage.x = storage.x/ -1000.0f;
	storage.y = storage.y/ -1000.0f;
	storage.z = storage.z / -1000.0f;

	Direction = storage;
}

bool Enemy::isColliding(Cannonball* obj)
{
	//get the corners of the bounding box
	//start by converting the bounds to world space
	//XMVECTOR thisMin = XMVectorMultiply(XMLoadFloat3(&mesh->getMinBound()), XMLoadFloat3(&transform.getScale()));
	XMVECTOR thisMin = XMVectorMultiplyAdd(XMLoadFloat3(&mesh->getMinBound()), XMLoadFloat3(&transform.getScale()), XMLoadFloat3(&transform.getPosition()));
	//thisMin = XMVectorAdd(thisMin, XMLoadFloat3(&transform.getPosition()));
	XMVECTOR objMin =  XMVectorMultiply(XMLoadFloat3(&obj->GetMesh()->getMinBound()), XMLoadFloat3(&obj->GetTransform()->getScale()));
	objMin = XMVectorAdd(objMin, XMLoadFloat3(&obj->GetTransform()->getPosition()));

	XMVECTOR thisMax = XMVectorMultiply(XMLoadFloat3(&mesh->getMaxBound()), XMLoadFloat3(&transform.getScale()));
	thisMax = XMVectorAdd(thisMax, XMLoadFloat3(&transform.getPosition()));
	XMVECTOR objMax = XMVectorMultiply(XMLoadFloat3(&obj->GetMesh()->getMaxBound()), XMLoadFloat3(&obj->GetTransform()->getScale()));
	objMax = XMVectorAdd(objMax, XMLoadFloat3(&obj->GetTransform()->getPosition()));

	//store the world space bounds into float3's
	XMFLOAT3 aMin;
	XMFLOAT3 aMax;
	XMFLOAT3 bMin;
	XMFLOAT3 bMax;

	XMStoreFloat3(&aMin, thisMin);
	XMStoreFloat3(&aMax, thisMax);
	XMStoreFloat3(&bMin, objMin);
	XMStoreFloat3(&bMax, objMax);

	//compare the bounds and see if they interesect
	if (aMin.x <= bMax.x && aMax.x >= bMin.x &&
		aMin.y <= bMax.y && aMax.y >= bMin.y &&
		aMin.z <= bMax.z && aMax.z >= bMin.z)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Enemy::isColliding(Entity* obj)
{
	//get the corners of the bounding box
//start by converting the bounds to world space
	XMVECTOR thisMin = XMVectorMultiply(XMLoadFloat3(&mesh->getMinBound()), XMLoadFloat3(&transform.getScale()));
	thisMin = XMVectorAdd(thisMin, XMLoadFloat3(&transform.getPosition()));
	XMVECTOR objMin = XMVectorMultiply(XMLoadFloat3(&obj->GetMesh()->getMinBound()), XMLoadFloat3(&obj->GetTransform()->getScale()));
	objMin = XMVectorAdd(objMin, XMLoadFloat3(&obj->GetTransform()->getPosition()));

	XMVECTOR thisMax = XMVectorMultiply(XMLoadFloat3(&mesh->getMaxBound()), XMLoadFloat3(&transform.getScale()));
	thisMax = XMVectorAdd(thisMax, XMLoadFloat3(&transform.getPosition()));
	XMVECTOR objMax = XMVectorMultiply(XMLoadFloat3(&obj->GetMesh()->getMaxBound()), XMLoadFloat3(&obj->GetTransform()->getScale()));
	objMax = XMVectorAdd(objMax, XMLoadFloat3(&obj->GetTransform()->getPosition()));

	//store the world space bounds into float3's
	XMFLOAT3 aMin;
	XMFLOAT3 aMax;
	XMFLOAT3 bMin;
	XMFLOAT3 bMax;

	XMStoreFloat3(&aMin, thisMin);
	XMStoreFloat3(&aMax, thisMax);
	XMStoreFloat3(&bMin, objMin);
	XMStoreFloat3(&bMax, objMax);

	//compare the bounds and see if they interesect 
	if (aMin.x <= bMax.x && aMax.x >= bMin.x &&
		aMin.y <= bMax.y && aMax.y >= bMin.y &&
		aMin.z <= bMax.z && aMax.z >= bMin.z)
	{
		return true;
	}
	else
	{
		return false;
	}
}


