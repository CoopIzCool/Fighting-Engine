#pragma once
#include <Windows.h>
#include <DirectXMath.h>
#include "Transform.h"


class Camera
{
public:
	Camera(float x, float y, float z, float aspect);
	~Camera();

	void Update(float dt, HWND windowHandle);
	void UpdateViewMatrix();
	void UpdateProjectionMatrix(float aspectRatio);

	DirectX::XMFLOAT4X4 GetViewMatrix();
	DirectX::XMFLOAT4X4 GetProjectionMatrix();

private:
	DirectX::XMFLOAT4X4 viewMatrix;
	DirectX::XMFLOAT4X4 projectionMatrix;
	Transform transform;
	POINT prevMouse;
};

