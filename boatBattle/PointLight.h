#pragma once

#include <DirectXMath.h>

struct PointLight
{
	DirectX::XMFLOAT3 color;
	float intensity;
	DirectX::XMFLOAT3 position;
};