#pragma once
#include "DXCore.h"
#include <DirectXMath.h>

class Material
{
public:
	Material(DirectX::XMFLOAT4 tint,
		Microsoft::WRL::ComPtr<ID3D11PixelShader> pixel,
		Microsoft::WRL::ComPtr<ID3D11VertexShader> vertex);

	~Material();

	DirectX::XMFLOAT4 GetColorTint();
	Microsoft::WRL::ComPtr<ID3D11PixelShader> GetPixelShader();
	Microsoft::WRL::ComPtr<ID3D11VertexShader> GetVertexShader();

	void SetColorTint(DirectX::XMFLOAT4 tint);

private:
	DirectX::XMFLOAT4 colorTint;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> pixShader;
	Microsoft::WRL::ComPtr<ID3D11VertexShader> vertShader;
};

