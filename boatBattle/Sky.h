#pragma once
#include "DXCore.h"
#include "Mesh.h"
#include "SimpleShader.h"
#include <DirectXMath.h>
#include <wrl/client.h>
#include "Camera.h"

class Sky
{
public:
	Sky(Mesh* drawnMesh, Microsoft::WRL::ComPtr<ID3D11SamplerState> sample,
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture,
		SimplePixelShader* pixel,
		SimpleVertexShader* vertex,
		Microsoft::WRL::ComPtr<ID3D11Device> deviceObject);
	void Draw(Microsoft::WRL::ComPtr<ID3D11DeviceContext> context,Camera* cam);

private:
	Microsoft::WRL::ComPtr<ID3D11SamplerState> sampler;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> textureSRV;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depth;
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizer;
	Mesh* mesh;
	SimplePixelShader* pixelShader;
	SimpleVertexShader* vertexShader;
};

