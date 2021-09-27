#pragma once
#include "DXCore.h"
#include "SimpleShader.h"
#include <DirectXMath.h>

class Material
{
public:
	Material(DirectX::XMFLOAT4 tint,
		SimplePixelShader* pixel,
		SimpleVertexShader* vertex,
		float specEx,
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture,
		Microsoft::WRL::ComPtr<ID3D11SamplerState> samp);

	Material(DirectX::XMFLOAT4 tint,
		SimplePixelShader* pixel,
		SimpleVertexShader* vertex,
		float specEx,
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture,
		Microsoft::WRL::ComPtr<ID3D11SamplerState> samp,
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> normal,
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> rough,
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> metalSRV);

	~Material();

	DirectX::XMFLOAT4 GetColorTint();
	SimplePixelShader* GetPixelShader();
	SimpleVertexShader* GetVertexShader();
	float Shininess();
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> GetTextureSRV();
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> GetNormalSRV();
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> GetRoughSRV();
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> GetMetalSRV();
	Microsoft::WRL::ComPtr<ID3D11SamplerState> GetSampler();

	void SetColorTint(DirectX::XMFLOAT4 tint);

private:
	DirectX::XMFLOAT4 colorTint;
	SimplePixelShader* pixelShader;
	SimpleVertexShader* vertexShader;
	float specExponent;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> textureSRV;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> normalSRV;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> roughSRV;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> metalSRV;
	Microsoft::WRL::ComPtr<ID3D11SamplerState> sampler;
};

