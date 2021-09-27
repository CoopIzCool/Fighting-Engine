#include "Camera.h"

using namespace DirectX;
Camera::Camera(float x, float y, float z, float aspect)
{
	transform.setPosition(x, y, z);

	UpdateViewMatrix();
	UpdateProjectionMatrix(aspect);
	freeMode = false;
}

Camera::~Camera()
{
}

void Camera::Update(float dt, HWND windowHandle)
{
	float speed = dt * 3.0f;

	//directions in develop mode
	if (freeMode)
	{
		if (GetAsyncKeyState('W') & 0x8000)
		{
			transform.MoveRelative(0, 0, speed);
		}
		if (GetAsyncKeyState('S') & 0x8000)
		{
			transform.MoveRelative(0, 0, -speed);
		}
		if (GetAsyncKeyState('A') & 0x8000)
		{
			transform.MoveRelative(-speed, 0, 0);
		}
		if (GetAsyncKeyState('D') & 0x8000)
		{
			transform.MoveRelative(speed, 0, 0);
		}
		if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		{
			transform.MoveRelative(0, speed, 0);
		}
		if (GetAsyncKeyState(VK_SHIFT) & 0x8000)
		{
			transform.MoveRelative(0, -speed, 0);
		}

		POINT mousePos{};
		GetCursorPos(&mousePos);
		ScreenToClient(windowHandle, &mousePos);

		//check if the mouse is clicked
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		{
			float xDiff = dt * (mousePos.x - prevMouse.x);
			float yDiff = dt * (mousePos.y - prevMouse.y);

			//rotate camera based on mouse movement
			transform.Rotate(yDiff, xDiff, 0);
		}
		UpdateViewMatrix();
		//store mouse's previous position as the current.... curent one
		prevMouse = mousePos;
	}
	else
	{
		//code for when the camera is in the game
		if (GetAsyncKeyState('A') & 0x8000)
		{
			transform.Rotate(0, -speed, 0);
		}
		if (GetAsyncKeyState('D') & 0x8000)
		{
			transform.Rotate(0, speed, 0);
		}
		/*
		if (GetAsyncKeyState(VK_SHIFT) & 0x8000)
		{
			freeMode = true;
		}
		*/

		UpdateViewMatrix();
		
	}


}

void Camera::UpdateViewMatrix()
{
	//get pitch/yaw/roll angles
	XMFLOAT3 pyr = transform.getRotation();
	//forward vector
	XMVECTOR forward = XMVector3Rotate(
		XMVectorSet(0, 0, 1, 0),
		XMQuaternionRotationRollPitchYawFromVector(XMLoadFloat3(&pyr)));
	//view vector
	XMFLOAT3 position = transform.getPosition();
	XMMATRIX view = XMMatrixLookToLH(
		XMLoadFloat3(&position), 
		forward, 
		XMVectorSet(0, 1, 0, 0));

	XMStoreFloat4x4(&viewMatrix, view);
}

void Camera::UpdateProjectionMatrix(float aspectRatio)
{
	XMMATRIX proj = XMMatrixPerspectiveFovLH(
		XM_PIDIV4,
		aspectRatio, 
		0.01f, 
		100.0f);

	XMStoreFloat4x4(&projectionMatrix, proj);
}



DirectX::XMFLOAT4X4 Camera::GetViewMatrix()
{
	return viewMatrix;
}

DirectX::XMFLOAT4X4 Camera::GetProjectionMatrix()
{
	return projectionMatrix;
}

DirectX::XMFLOAT3 Camera::getPosition()
{
	return transform.getPosition();
}

Transform Camera::getTransform()
{
	return transform;
}

bool Camera::isFree()
{
	return freeMode;
}
