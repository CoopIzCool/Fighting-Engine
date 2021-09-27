#pragma once

#include <DirectXMath.h>

class Transform
{
public:
	Transform();
	~Transform();

	void MoveAbsolute(float x, float y, float z);
	void MoveRelative(float x, float y, float z);
	void Rotate(float pitch, float yaw, float roll);
	void Scale(float x, float y, float z);

	void setPosition(float x, float y, float z);
	void setRotate(float pitch, float yaw, float roll);
	void setScale(float x, float y, float z);

	DirectX::XMFLOAT3 getPosition();
	DirectX::XMFLOAT3 getRotation();
	DirectX::XMFLOAT3 getScale();

	DirectX::XMFLOAT4X4 GetWorldMatrix();

	void updateWorld();
	DirectX::XMFLOAT4X4 lookAt(DirectX::XMFLOAT3 pos);
private:
	DirectX::XMFLOAT4X4 world;
	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT3 rotation;
	DirectX::XMFLOAT3 scale;
	bool isDirty;

};

