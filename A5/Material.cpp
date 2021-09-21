#include "Material.h"

using namespace DirectX;
Material::Material(DirectX::XMFLOAT4 tint, Microsoft::WRL::ComPtr<ID3D11PixelShader> pixel, Microsoft::WRL::ComPtr<ID3D11VertexShader> vertex)
{
	colorTint = tint;
	pixShader = pixel;
	vertShader = vertex;
}

Material::~Material()
{
}

DirectX::XMFLOAT4 Material::GetColorTint()
{
	return colorTint;
}

Microsoft::WRL::ComPtr<ID3D11PixelShader> Material::GetPixelShader()
{
	return pixShader;
}

Microsoft::WRL::ComPtr<ID3D11VertexShader> Material::GetVertexShader()
{
	return vertShader;
}

void Material::SetColorTint(DirectX::XMFLOAT4 tint)
{
	colorTint = tint;
}
