#include "Material.h"

using namespace DirectX;
Material::Material(DirectX::XMFLOAT4 tint, SimplePixelShader* pixel,SimpleVertexShader* vertex, float specEx, 
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture, Microsoft::WRL::ComPtr<ID3D11SamplerState> samp)
{
	colorTint = tint;
	pixelShader = pixel;
	vertexShader = vertex;
	specExponent = specEx;
	textureSRV = texture;
	sampler = samp;
	normalSRV = nullptr;
}

Material::Material(DirectX::XMFLOAT4 tint, SimplePixelShader* pixel, SimpleVertexShader* vertex, float specEx, 
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture, Microsoft::WRL::ComPtr<ID3D11SamplerState> samp, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> normal, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> rough,Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> metal)
{
	colorTint = tint;
	pixelShader = pixel;
	vertexShader = vertex;
	specExponent = specEx;
	textureSRV = texture;
	sampler = samp;
	normalSRV = normal;
	roughSRV = rough;
	metalSRV = metal;
}

Material::~Material()
{
}

DirectX::XMFLOAT4 Material::GetColorTint()
{
	return colorTint;
}

SimplePixelShader* Material::GetPixelShader()
{
	return pixelShader;
}

SimpleVertexShader* Material::GetVertexShader()
{
	return vertexShader;
}

float Material::Shininess()
{
	return specExponent;
}

Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> Material::GetTextureSRV()
{
	return textureSRV;
}

Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> Material::GetNormalSRV()
{
	return normalSRV;
}

Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> Material::GetRoughSRV()
{
	return roughSRV;
}

Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> Material::GetMetalSRV()
{
	return metalSRV;
}

Microsoft::WRL::ComPtr<ID3D11SamplerState> Material::GetSampler()
{
	return sampler;
}

void Material::SetColorTint(DirectX::XMFLOAT4 tint)
{
	colorTint = tint;
}
