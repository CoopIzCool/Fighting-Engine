#include "Transform.h"

using namespace DirectX;

Transform::Transform()
{
	position = XMFLOAT3(0, 0, 0);
	rotation = XMFLOAT3(0, 0, 0);
	scale = XMFLOAT3(1, 1, 1);
	updateWorld();
}

Transform::~Transform()
{
}

void Transform::MoveAbsolute(float x, float y, float z)
{
	XMVECTOR newPos = XMVectorAdd(XMLoadFloat3(&position), XMVectorSet(x, y, z, 0));
	XMStoreFloat3(&position, newPos);
	isDirty = true;
}

void Transform::MoveRelative(float x, float y, float z)
{
	XMVECTOR desiredMovement = XMVectorSet(x, y, z, 0);
	//current rotation in quaterninons 
	XMVECTOR rotateQuat = XMQuaternionRotationRollPitchYawFromVector(XMLoadFloat3(&rotation));

	//rotate desired movement by same amoutn needed
	XMVECTOR relativeMovement = XMVector3Rotate(desiredMovement, rotateQuat);

	XMStoreFloat3(&position, XMLoadFloat3(&position) + relativeMovement);
	isDirty = true;
}

void Transform::Rotate(float pitch, float yaw, float roll)
{
	XMVECTOR newRotate = XMVectorAdd(XMLoadFloat3(&rotation), XMVectorSet(pitch, yaw, roll, 0));
	XMStoreFloat3(&rotation, newRotate);
	isDirty = true;

}

void Transform::Scale(float x, float y, float z)
{

	XMVECTOR newScale = XMVectorAdd(XMLoadFloat3(&scale), XMVectorSet(x, y, z, 0));
	XMStoreFloat3(&scale, newScale);

	isDirty = true;
}

void Transform::setPosition(float x, float y, float z)
{
	position.x = x;
	position.y = y;
	position.z = z;
	isDirty = true;
}

void Transform::setRotate(float pitch, float yaw, float roll)
{
	rotation.x = pitch;
	rotation.y = yaw;
	rotation.z = roll;
	isDirty = true;
}

void Transform::setScale(float x, float y, float z)
{
	scale.x = x;
	scale.y = y;
	scale.z = z;
	isDirty = true;
}

DirectX::XMFLOAT3 Transform::getPosition()
{
	return position;
}

DirectX::XMFLOAT3 Transform::getRotation()
{
	return rotation;
}

DirectX::XMFLOAT3 Transform::getScale()
{
	return scale;
}

DirectX::XMFLOAT4X4 Transform::GetWorldMatrix()
{
	if (isDirty)
	{
		updateWorld();
	}

	return world;
}

void Transform::updateWorld()
{
	XMMATRIX Translation = XMMatrixTranslationFromVector(XMLoadFloat3(&position));
	XMMATRIX Rotation = XMMatrixRotationRollPitchYawFromVector(XMLoadFloat3(&rotation));
	XMMATRIX Scale = XMMatrixScalingFromVector(XMLoadFloat3(&scale));

	XMMATRIX worldMat = Scale * Rotation * Translation;

	XMStoreFloat4x4(&world, worldMat);
	isDirty = false;
}

DirectX::XMFLOAT4X4 Transform::lookAt(DirectX::XMFLOAT3 pos)
{
	XMVECTOR location = XMLoadFloat3(&position);
	XMVECTOR looking = XMLoadFloat3(&pos);
	XMVECTOR up = XMVectorSet(0, 1, 0, 0);
	XMMATRIX viewMatrix = XMMatrixLookAtLH(location, looking, up);
	XMMATRIX Scale = XMMatrixScalingFromVector(XMLoadFloat3(&scale));
	XMMATRIX Rotation = XMMatrixRotationRollPitchYawFromVector(XMLoadFloat3(&rotation));

	XMMATRIX invert =  Scale * Rotation *  XMMatrixInverse(nullptr, viewMatrix);

	XMStoreFloat4x4(&world, invert);
	
	return world;
	//XMStoreFloat3(&rotation, )
}
